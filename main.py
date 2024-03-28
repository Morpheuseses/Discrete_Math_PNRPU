import numpy as np
import cv2 as cv
import os
from PIL import Image

import track
 
cap = cv.VideoCapture(0)
if not cap.isOpened():
    print("Cannot open camera")
    exit()
i = 0;
while True:
    # Capture frame-by-frame
    ret, frame = cap.read()
    frame = cv.cvtColor(frame, cv.COLOR_BGR2RGB)
    #img = Image.fromarray(frame, 'RGB')
    # print (frame)

    fullpath = os.path.join('/home/morph/Documents/programming/torch/video_capture/images', str(i)+'.jpg')
    #img.save(fullpath)
    img = track.detect(Image.fromarray(frame, 'RGB'))
    img.save(fullpath)
    frame = np.array(img)
    
 # if frame is read correctly ret is True
    if not ret:
        print("Can't receive frame (stream end?). Exiting ...")
        break
 # Our operations on the frame come here
    gray = cv.cvtColor(frame, cv.COLOR_BGR2RGB)
 # Display the resulting frame
    cv.imshow('frame', gray)
    if cv.waitKey(1) == ord('q'):
        break
    i += 1
 
# When everything done, release the capture
cap.release()
cv.destroyAllWindows()