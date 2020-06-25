from flask import Flask, render_template, Response
from Camera import Camera

cap= Camera()
cap.run()

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

def gen(cap):
    while True:
        frame = cap.get_frame()
        yield (b'--frame\r\n'
               b'Content-Type: image/png\r\n\r\n' + frame + b'\r\n')
    cap.release()

@app.route('/video_feed')
def video_feed():
    return Response(gen(cap),
                    mimetype='multipart/x-mixed-replace; boundary=frame')

if __name__ == '__main__':
        app.run(host='0.0.0.0')

