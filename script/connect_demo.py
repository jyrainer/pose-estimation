# import RPi.GPIO as gpio
# import serial

import cv2
import numpy as np

class ImageDrawer:
    def __init__(self, image_path):
        self.image = cv2.imread(image_path)
        self.shapes = []

    def add_circle(self, center, radius, color, thickness):
        self.shapes.append(('circle', center, radius, color, thickness))

    def add_line(self, start_point, end_point, color, thickness):
        self.shapes.append(('line', start_point, end_point, color, thickness))

    def draw_shapes(self):
        for shape in self.shapes:
            if shape[0] == 'circle':
                center, radius, color, thickness = shape[1:]
                cv2.circle(self.image, center, radius, color, thickness)
            elif shape[0] == 'line':
                start_point, end_point, color, thickness = shape[1:]
                cv2.line(self.image, start_point, end_point, color, thickness)

    def show_image(self):
        cv2.imshow("test",self.image)
        cv2.waitKey(0)
        cv2.destroyAllWindows()
        
a_l = [None] * 96
# 예시입력
a_l = [0,0,0,0,0,0,0,0,
       0,0,5,52,45,3,0,0,
       0,0,0,40,45,0,0,0,
       0,0,40,50,50,42,5,0,
       0,40,40,50,50,43,40,0,
       0,40,45,56,56,45,40,0,
       0,45,4,60,60,5,45,0,
       0,5,25,67,76,20,4,0,
       0,0,5,67,76,20,4,0,
       0,0,5,67,76,20,4,0,
       0,0,5,20,30,20,4,0,
       0,0,0,0,0,0,0,0,
       ]


threshold = 40  # 인식되었다고 할 최소 임계값 설정

a_l_2d = [a_l[i:i+8] for i in range(0, len(a_l), 8)]    # a_l을 12열 8행 리스트로 변환
a_l_2d_bool = [[1 if element >= threshold else 0 for element in row] for row in a_l_2d] #a_l_2d를 부울화 시킴

image_drawer = ImageDrawer("./white_800_650.png")       # 임의의 이미지는 800x650 사이즈를 가집니다.
width, height = (800,650)
width_cell, height_cell = (width/12,height/8)

# 얼굴 인식 inference 값이 다음고 같이 나온다고 가정합니다.
xmin, ymin, xmax, ymax = [200,81.25,334,243.75]

# 발위치의 좌표를 찾기 위해, 아래의 행부터 스캔하여 하나라도 1이 발견되는 그 행이 fb입니다.
for i in range(len(a_l_2d_bool) - 1, -1, -1):
    if 1 in a_l_2d_bool[i]:
        fb = i*height_cell
        break

h = fb - ymin # 가장 아래 y좌표 - 머리에 감지된 가장 위 y좌표. 즉 환자의 키 추정치이다. (1)
R = ymin + h*0.55 # 환자의 중심점. 몸의 중심이 되는 y좌표값임                          (2)

head_middle_x = (xmax+xmin)/2
ymax_index = int(ymax // height_cell)    # 머리 아랫부분 y 인덱스
shoulder_y_index = ymax_index            # 어깨 y 인덱스

# shoulder_y_index 행에서 처음으로 1이 되는 열 인덱스 출력
for j in range(len(a_l_2d_bool[shoulder_y_index])):
    if a_l_2d_bool[shoulder_y_index][j] == 1:
        shoulder_xmin_index = j
        break

# shoulder_y_index 행에서 끝의 열부터 스캔하여 처음으로 1이 나오는 인덱스 출력
for j in range(len(a_l_2d_bool[shoulder_y_index]) - 1, -1, -1):
    if a_l_2d_bool[shoulder_y_index][j] == 1:
        shoulder_xmax_index = j
        break

# 초기값 설정
left_max_row_index = None
right_max_row_index =None

# 열을 스캔하면서 처음으로 1이 발견된 열에서 가장 큰 행 인덱스 찾기
for j in range(len(a_l_2d_bool[0])):
    for i in range(len(a_l_2d_bool)):
        if a_l_2d_bool[i][j] == 1:
            left_max_row_index = i  # 처음으로 1이 발견된 행의 인덱스로 초기화
    if left_max_row_index is not None:
        break  # 이미 left_max_row_index 업데이트되었으면 더 이상 열 스캔을 할 필요 없음
        
# 열을 역순으로 스캔하면서 처음으로 1이 발견된 열에서 가장 큰 행 인덱스 찾기
for j in range(len(a_l_2d_bool[0]) - 1, -1, -1):
    for i in range(len(a_l_2d_bool)):
        if a_l_2d_bool[i][j] == 1:
            right_max_row_index = i  # 1이 발견되면 행 인덱스 업데이트
    if right_max_row_index is not None:
        break  # 이미 right_max_row_index 업데이트되었으면 더 이상 열 스캔을 할 필요 없음


# 1이 존재하는 최하단 행에서 가장 낮은 인덱스와 가장 큰 인덱스 찾기
lowest_index = None
highest_index = None

for row in reversed(a_l_2d_bool):
    if 1 in row:
        lowest_index = row.index(1)
        highest_index = max(i for i, x in enumerate(row) if x == 1)
        break

# Joint
joint1 = (int(head_middle_x),int(ymin))
joint2 = (int(head_middle_x),int(ymax))
joint3 = (int(shoulder_xmin_index*width_cell), int(ymax+1*height_cell))
joint4 = (int(shoulder_xmin_index*width_cell), int( (left_max_row_index*height_cell + (ymax+1*height_cell) )/2))
joint5 = (int(shoulder_xmin_index*width_cell), int(left_max_row_index*height_cell) )
joint6 = (int(shoulder_xmax_index*width_cell), int(ymax+1*height_cell))
joint7 = (int(shoulder_xmax_index*width_cell), int((right_max_row_index*height_cell + (ymax+1*height_cell))/2))
joint8 = (int(shoulder_xmax_index*width_cell), int(right_max_row_index*height_cell) )
joint9 = (int(head_middle_x),int(R))
joint10 = (int(lowest_index*width_cell),int(R + (fb-R)/2 ))
joint11 = (int(lowest_index*width_cell),int(fb))
joint12 = (int(highest_index*width_cell),int(R + (fb-R)/2 ))
joint13 = (int(highest_index*width_cell),int(fb))

# connection
connection1 = (joint1,joint2)
connection2 = (joint2,joint3)
connection3 = (joint3,joint4)
connection4 = (joint4,joint5)
connection5 = (joint2,joint6)
connection6 = (joint6,joint7)
connection7 = (joint7,joint8)
connection8 = (joint2,joint9)
connection9 = (joint9,joint10)
connection10 = (joint10,joint11)
connection11 = (joint9,joint12)
connection12 = (joint12,joint13)

red = (0, 0, 0)
color = (0,0,255)

image_drawer.add_circle(joint1, 4, color, 1)
image_drawer.add_circle(joint2, 4, color, 1)
image_drawer.add_circle(joint3, 4, color, 1)
image_drawer.add_circle(joint4, 4, color, 1)
image_drawer.add_circle(joint5, 4, color, 1)
image_drawer.add_circle(joint6, 4, color, 1)
image_drawer.add_circle(joint7, 4, color, 1)
image_drawer.add_circle(joint8, 4, color, 1)
image_drawer.add_circle(joint9, 4, color, 1)
image_drawer.add_circle(joint10, 4, color, 1)
image_drawer.add_circle(joint11, 4, color, 1)
image_drawer.add_circle(joint12, 4, color, 1)
image_drawer.add_circle(joint13, 4, color, 1)


image_drawer.add_line(*connection1,red, 2)
image_drawer.add_line(*connection2,red, 2)
image_drawer.add_line(*connection3,red, 2)
image_drawer.add_line(*connection4,red, 2)
image_drawer.add_line(*connection5,red, 2)
image_drawer.add_line(*connection6,red, 2)
image_drawer.add_line(*connection7,red, 2)
image_drawer.add_line(*connection8,red, 2)
image_drawer.add_line(*connection9,red, 2)
image_drawer.add_line(*connection10,red, 2)
image_drawer.add_line(*connection11,red, 2)
image_drawer.add_line(*connection12,red, 2)

image_drawer.draw_shapes()
image_drawer.show_image()