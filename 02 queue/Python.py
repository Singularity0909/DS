from flask import Flask, request
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
        tot = '当前队列中共有 ' + str(len(q)) + ' 人\n'
        if q.count(id):
            return tot + '您在队列中的位置为 ' + str(q.index(id) + 1)
        else:
            return tot + '您不在队列中 等待扫码'


def qpop():
    while True:
        time.sleep(20)
        if q:
            q.pop(0)


if __name__ == '__main__':
    t = threading.Thread(target=qpop)
    t.start()
    app.run(debug=True, host='0.0.0.0', port=666)
    t.join()
