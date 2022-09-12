import cv2
import numpy as np
import function

cap = cv2.VideoCapture(0)

cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)

cap.set(cv2.CAP_PROP_FOURCC, cv2.VideoWriter.fourcc("M", "J", "P", "G"))  # ?1为啥要重设
while cap.isOpened():
    ret, frame = cap.read()
    cv2.imshow('picture', frame)

    # frame = cv2.GaussianBlur(frame, (5, 5), 0, 0)
    frame = cv2.blur(frame, (5, 5))
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    cv2.imshow("gray", gray)

    binary = cv2.Canny(gray, 40, 48)
    # cv2.imshow("binary", binary)
    dilation = cv2.dilate(binary, cv2.getStructuringElement(cv2.MORPH_RECT, (25, 25)))
    # cv2.imshow("dilation", dilation)

    contours, hierarchy = cv2.findContours(dilation, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)

    if np.array(contours, dtype=object).size != 0:
        i = function.square(contours)
        trans = np.reshape(contours[i], (-1, 2))
        a = function.order_points(trans)
        pic = function.transform(frame, a)
        # b = np.reshape(a, (1, -1, 2)).astype(int)
        # pic = cv2.drawContours(frame, b, -1, (0, 255, 0), 5)

        cv2.imshow('pic', pic)

        hsv = cv2.cvtColor(pic, cv2.COLOR_BGR2HSV)

        minBlue = np.array([0, 50, 50])
        maxBlue = np.array([255, 255, 255])
        # 确定蓝色区域
        mask = cv2.inRange(hsv, minBlue, maxBlue)

        mask = cv2.GaussianBlur(mask, (15, 15), 0, 0)
        retval, mask = cv2.threshold(mask, 0, 255, cv2.THRESH_OTSU)
        cv2.imshow('mask', mask)

        kernel = np.ones((9, 9), np.uint8)
        erosion = cv2.erode(mask, kernel)
        erosion = cv2.dilate(erosion, cv2.getStructuringElement(cv2.MORPH_RECT, (5, 5)))
        erosion = cv2.erode(erosion, kernel)
        erosion = cv2.dilate(erosion, cv2.getStructuringElement(cv2.MORPH_RECT, (5, 5)))
        erosion = cv2.erode(erosion, kernel)
        erosion = cv2.dilate(erosion, cv2.getStructuringElement(cv2.MORPH_RECT, (5, 5)))
        erosion = cv2.erode(erosion, kernel)
        erosion = cv2.dilate(erosion, cv2.getStructuringElement(cv2.MORPH_RECT, (5, 5)))
        erosion = cv2.erode(erosion, kernel)
        erosion = cv2.dilate(erosion, cv2.getStructuringElement(cv2.MORPH_RECT, (5, 5)))
        erosion = cv2.erode(erosion, kernel)

        cv2.imshow('erosion', erosion)
        print(function.find_white(erosion))
        # 通过掩码控制的按位与运算，锁定蓝色区域
        color = cv2.bitwise_and(pic, pic, mask=mask)
        cv2.imshow('color', color)
        color2gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        # pic2 = cv2.Canny(pic, 16, 40)
        # pic2 = cv2.dilate(pic2, cv2.getStructuringElement(cv2.MORPH_RECT, (5, 5)))  # , iterations=3
        # # pic2 = cv2.blur(pic2, (15, 15))
        # cv2.imshow('pic2', pic2)
        #
        # contours, hierarchy = cv2.findContours(pic2, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        # pic = cv2.drawContours(pic, contours, -1, (0, 0, 255), 5)

        # cv2.imshow('pic3', pic)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
cap.release()
cv2.destroyAllWindows()
