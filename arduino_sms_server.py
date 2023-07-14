from http.server import BaseHTTPRequestHandler, HTTPServer
import urllib.parse
import serial
# TODO: Configure the serial port connection to the Arduino
ser = serial.Serial('/dev/cu.usbserial-0001', 9600)  # Replace with the appropriate serial port and baud rate

# HTTPRequestHandler class
class RequestHandler(BaseHTTPRequestHandler):
    def do_POST(self):
        if self.path == '/sms-webhook':
            content_length = int(self.headers['Content-Length'])
            body = self.rfile.read(content_length).decode('utf-8')
            self.send_response(200)
            self.end_headers()
            print('Received body:', body)

            try:
                # Parse the form data
                parsed_body = urllib.parse.parse_qs(body)
                sender = parsed_body['From'][0]
                message_body = parsed_body['Body'][0]

                # Send the received SMS data to the Arduino
                message = f'From: {sender} - Message: {message_body}'
                ser.write(message.encode())

                print('SMS data sent to Arduino:', message)
            except KeyError as e:
                print('Missing key in form data:', str(e))
        else:
            self.send_response(404)
# Set up and start the server
def run():
    server_address = ('0.0.0.0', 3000)  # Use the wildcard address
    httpd = HTTPServer(server_address, RequestHandler)
    print('Server is running on port 3000')
    httpd.serve_forever()

run()

