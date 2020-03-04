from flask import Flask, request, jsonify
import time
import threading

app = Flask(__name__)
q = []


@app.route('/', methods=['POST', 'GET'])
def getId():
    if request.method == 'POST':
        id = request.headers.get('Id')
        if q.count(id):
            return '您已经在队列中'
        else:
            q.append(id)
            return '成功加入队列'
    if request.method == 'GET':
        id = request.args.get('id')
        size = len(q)
        pos = 0
        if q.count(id):
            pos = q.index(id) + 1
        return jsonify({'size': size, 'pos': pos})


def qpop():
    while True:
        time.sleep(5)
        if q:
            q.pop(0)


if __name__ == '__main__':
    t = threading.Thread(target=qpop)
    t.start()
    app.run(debug=True, host='0.0.0.0', port=666)
    t.join()
