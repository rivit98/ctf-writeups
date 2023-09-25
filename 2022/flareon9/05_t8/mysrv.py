from http.server import BaseHTTPRequestHandler, HTTPServer
from wireshark import first_response, second_response
first = True
class handler(BaseHTTPRequestHandler):
    def do_POST(self):
        global first

        print(f"Got request first? {first}")
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()

        if first is True:
            self.wfile.write(bytes(first_response, "utf8"))
            first = False
        else:
            self.wfile.write(bytes(second_response, "utf8"))

with HTTPServer(('', 80), handler) as server:
    server.serve_forever()