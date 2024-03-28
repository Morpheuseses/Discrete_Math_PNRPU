from facenet_pytorch import MTCNN
import torch
import numpy as np
import cv2
from PIL import Image, ImageDraw


device = torch.device('cpu')

print (device)


mtcnn = MTCNN(keep_all=True, device=device)


def detect(frame):
    boxes, _ = mtcnn.detect(frame)

    frame_draw = frame.copy()
    draw = ImageDraw.Draw(frame_draw)
    for box in boxes:
        draw.rectangle(box.tolist(), outline=(255, 0, 0), width=6)

    return frame_draw

