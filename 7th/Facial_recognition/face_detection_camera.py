import face_recognition
import cv2
import os

KNOWN_FACES_DIR = 'known_faces'
TOLERANCE = 0.6
FONT = cv2.FONT_HERSHEY_SIMPLEX
FONT_SCALE = 0.6
FONT_THICKNESS = 2
MODEL = 'cnn'  # 'hog' or 'cnn', choose CNN if available for better accuracy

def name_to_color(name):
    color = [(ord(c.lower())-97)*8 for c in name[:3]]
    return color

print('Loading known faces...')
known_faces = []
known_names = []

for name in os.listdir(KNOWN_FACES_DIR):
    for filename in os.listdir(f'{KNOWN_FACES_DIR}/{name}'):
        image = face_recognition.load_image_file(f'{KNOWN_FACES_DIR}/{name}/{filename}')
        encoding = face_recognition.face_encodings(image)[0]
        known_faces.append(encoding)
        known_names.append(name)


cap = cv2.VideoCapture(1)

while True:
    ret, frame = cap.read()
    if not ret:
        break
    
    frame = cv2.flip(frame, 1)  # Flip the frame horizontally
    
    rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    face_locations = face_recognition.face_locations(rgb_frame, model=MODEL)
    face_encodings = face_recognition.face_encodings(rgb_frame, face_locations)
    
    for face_encoding, face_location in zip(face_encodings, face_locations):
        matches = face_recognition.compare_faces(known_faces, face_encoding, tolerance=TOLERANCE)
        name = "Unknown"
        
        if True in matches:
            match_index = matches.index(True)
            name = known_names[match_index]
        
        top_left = (face_location[3], face_location[0])
        bottom_right = (face_location[1], face_location[2])
        color = name_to_color(name)
        
        cv2.rectangle(frame, top_left, bottom_right, color, FONT_THICKNESS)
        cv2.putText(frame, name, (face_location[3], face_location[2] + 20), FONT, FONT_SCALE, color, FONT_THICKNESS)
    
    cv2.imshow('Face Recognition', frame)
    
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
