import cv2
import numpy as np

import function

cap = cv2.VideoCapture(0)
while cap.isOpened():
    ret, frame = cap.read()
    cv2.imshow('picture', frame)
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    cv2.imshow("gray", gray)
    binary = cv2.Canny(gray, 70, 200)
    binary = cv2.dilate(binary, cv2.getStructuringElement(cv2.MORPH_RECT, (5, 5)))
    contours, hierarchy = cv2.findContours(binary, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)

    if np.array(contours, dtype=object).size != 0:
        i = function.square(contours)
        trans = np.reshape(contours[i], (-1, 2))
        a = function.order_points(trans)
        pic = function.transform(gray, a)
        cv2.imshow('pic', pic)
    else:
        pic = gray
    # retval, dst = cv2.threshold(gray, 0, 255, cv2.THRESH_OTSU)
    # cv2.imshow("dst", dst)
    params = cv2.SimpleBlobDetector_Params()
    # 设置阈值
    params.minThreshold = 10
    params.maxThreshold = 200
    # 设置选择颜色
    params.filterByColor = True
    params.blobColor = 255
    # 设置选择区域
    params.filterByArea = True
    params.maxArea = 50000
    params.minArea = 200
    # 设置圆度
    params.filterByCircularity = True
    params.minCircularity = 0.1
    # 设置凸度
    params.filterByConvexity = True
    params.minConvexity = 0.87
    # 设置惯性比
    params.filterByInertia = True
    params.minInertiaRatio = 0.01
    detector = cv2.SimpleBlobDetector_create(params)
    keypoints = detector.detect(pic)
    print(len(keypoints))
    with_keypoints = cv2.drawKeypoints(pic, keypoints, np.array([]),
                                       (0, 0, 255), cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
    cv2.imshow("Keypoints", with_keypoints)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
cap.release()
cv2.destroyAllWindows()
