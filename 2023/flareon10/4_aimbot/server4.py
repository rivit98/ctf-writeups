from flask import Flask
from flask import request


app = Flask(__name__)


@app.route("/stolen",  methods=['POST'])
def stolen():
    print(request.headers)
    with open("dump", "wb") as f:
        f.write(request.data)
    return "AAAAAAA", 200


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=443)
