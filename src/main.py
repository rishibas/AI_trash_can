from ultralytics import YOLO
import cv2
import serial
import time

# Load a model
model = YOLO("best_1.pt")

ser = None
# # setup serial communication
ser = serial.Serial(
    port = 'COM4',
    baudrate= 115200,
    timeout=1,
    rtscts = False,
    dsrdtr = False,
    )
print(ser.name)
ser.setDTR(False) #serial.Serial()でArduinoがリセットされるのを防ぐ役割

# start Web camera.
# カメラの解像度が低い場合は、ここでcap.set()で高い解像度を設定することを推奨
cap = cv2.VideoCapture(0)

# カメラが開けない場合は終了
if not cap.isOpened():
    print("Error: Webカメラを開けませんでした。")
    exit()

# 推論ループ
while cap.isOpened():
    ret, frame = cap.read()
    if not ret:
        print("Error: フレームの読み込みに失敗しました。")
        break
    
    # 1. YOLOでフレーム解析 (show=Falseまたは非設定にする)
    # 結果は 'res' に格納される
    res = model(frame, verbose=False) # verbose=False でコンソール出力を減らす

    for box in res[0].boxes:
        class_id = int(box.cls)
        conf = float(box.conf) * 100 #%に変換
        label = res[0].names[class_id]
        if (label == "metal" and conf >= 80):
            print("検出label", label)
            print("信頼度", conf)
            if ser is not None:
                print("====")
                ser.write(b'1')
            time.sleep(1)


    # 2. 結果の描画
    # .plot() メソッドで、検出結果が描画された NumPy 配列（画像）を取得
    annotated_frame = res[0].plot()
    #print(res[0].boxes.conf)
    #print(res[0].boxes.cls)

    # 3. OpenCVで表示を制御
    # ここでウィンドウが常に開いたままになる
    cv2.imshow("YOLOv8 Real-Time Detection (Garbage AI)", annotated_frame)
    
    # 4. キー入力を待機 (30ms)
    # 'q'キーが押されたらループを抜ける
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# ループ終了後、リソースを解放
ser.close()
cap.release()
cv2.destroyAllWindows()
