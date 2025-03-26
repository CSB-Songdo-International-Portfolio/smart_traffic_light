import cv2
from ultralytics import YOLO
import serial
import time

# Initialize serial communication
ser = serial.Serial('COM10', 9600)  # Replace 'COM3' with the appropriate port
time.sleep(2)  # Wait for the serial connection to establish

# Load the YOLO model
model = YOLO("yolo11n.pt")

# Open the video file (0 for webcam)
video_path = 2
cap = cv2.VideoCapture(video_path)

# Loop through the video frames
while cap.isOpened():
    # Read a frame from the video
    success, frame = cap.read()

    if success:
        # Run YOLO inference on the frame
        results = model(frame)

        # Initialize counters for people and cars
        person_count = 0
        car_count = 0

        # Loop through each detected object
        for result in results[0].boxes:
            # Get the class ID of the detected object
            class_id = int(result.cls)

            # Check if the detected object is a person (class ID 0) or a car (class ID 2)
            if class_id == 0:  # Person
                person_count += 1
            elif class_id == 2:  # Car
                car_count += 1

        # Visualize the results on the frame
        annotated_frame = results[0].plot()

        # Display the counts on the frame
        cv2.putText(annotated_frame, f"People: {person_count}", (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
        cv2.putText(annotated_frame, f"Cars: {car_count}", (10, 70), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)

        # Display the annotated frame
        cv2.imshow("YOLO Inference", annotated_frame)

        # Send the counts as integers over serial (in the format: person_count,car_count)
        ser.write(f"{person_count},{car_count}\n".encode())
        time.sleep(2)
        # Break the loop if 'q' is pressed
        if cv2.waitKey(1) & 0xFF == ord("q"):
            break
    else:
        # Break the loop if the end of the video is reached
        break

# Release the video capture object and close the display window
cap.release()
cv2.destroyAllWindows()

# Close the serial connection
ser.close()
