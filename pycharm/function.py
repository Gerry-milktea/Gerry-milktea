import cv2
import numpy as np

'''
参数:pts为二维矩阵
功能:寻找四边形的的四个角
'''


def order_points(pts):
    rect = np.zeros((4, 2), dtype="float32")
    s = np.sum(pts, axis=1)
    rect[0] = pts[np.argmin(s)]
    rect[2] = pts[np.argmax(s)]
    diff = np.diff(pts, axis=1)
    rect[1] = pts[np.argmin(diff)]
    rect[3] = pts[np.argmax(diff)]
    return rect


'''
参数:cnts为 cv2.findContours 函数的返回值 contours
功能:从轮廓中找面积最大的四边形
'''


def square(cnts):
    if len(cnts) > 0:
        i = -1
        # 按轮廓面积降序排列
        cnts = sorted(cnts, key=cv2.contourArea, reverse=True)
        for c in cnts:
            # 近似轮廓
            peri = cv2.arcLength(c, True)  # 获取轮廓周长
            approx = cv2.approxPolyDP(c, 0.02 * peri, True)  # 多边形拟合，输出多边形顶点
            i = i + 1
            # 如果我们的近似轮廓有四个顶点，则确定找到了文档
            if len(approx) == 4:
                break
    return i


'''
功能:透视变换
'''


def transform(picture, dot):
    dst = np.array([
        [0, 0],
        [640, 0],
        [640, 480],
        [0, 480]], dtype="float32")
    M = cv2.getPerspectiveTransform(dot, dst)
    warped = cv2.warpPerspective(picture, M, (640, 480))
    return warped


def find_white(pic):
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
    params.maxCircularity = 1
    params.minCircularity = 0.01
    # 设置凸度
    params.filterByConvexity = True
    params.minConvexity = 0.87
    # 设置惯性比
    params.filterByInertia = True
    params.minInertiaRatio = 0.01
    detector = cv2.SimpleBlobDetector_create(params)
    keypoints = detector.detect(pic)
    # print(len(keypoints))
    with_keypoints = cv2.drawKeypoints(pic, keypoints, np.array([]),
                                       (0, 0, 255), cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
    cv2.imshow("Keypoints", with_keypoints)
    return len(keypoints)
