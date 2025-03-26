int person_count = 0;
int car_count = 0;

#define CAR_RED_PIN 2
#define CAR_GREEN_PIN 3
#define CAR_YELLOW_PIN 4

#define PERSON_RED 5
#define PERSON_GREEN 6

void setup() {
  // Start the serial communication at 9600 baud rate
  pinMode(CAR_RED_PIN, OUTPUT);
  pinMode(CAR_GREEN_PIN, OUTPUT);
  pinMode(CAR_YELLOW_PIN, OUTPUT);
  pinMode(PERSON_RED, OUTPUT);
  pinMode(PERSON_GREEN, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // Check if there is data available to read
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');  // Read until a newline character

    // Split the string into person_count and car_count based on the comma
    int commaIndex = data.indexOf(',');
    if (commaIndex != -1) {
      person_count = data.substring(0, commaIndex).toInt();  // Extract and convert person_count
      car_count = data.substring(commaIndex + 1).toInt();  // Extract and convert car_count

      // Print the counts to the Serial Monitor
      Serial.print("Person Count: ");
      Serial.println(person_count);
      Serial.print("Car Count: ");
      Serial.println(car_count);
    }
  }

  // Logic for controlling traffic lights based on person_count and car_count
  if (person_count > car_count) {
    // If there are more people than cars, set pedestrian light to green
    digitalWrite(PERSON_GREEN, LOW);  // Turn on pedestrian green light
    digitalWrite(PERSON_RED, HIGH);     // Turn off pedestrian red light

    // Turn off car lights
    digitalWrite(CAR_GREEN_PIN, LOW);  // Turn off car green light
    digitalWrite(CAR_RED_PIN, LOW);   // Turn on car red light
    digitalWrite(CAR_YELLOW_PIN, HIGH);   // Turn off car yellow light

    delay(2000);

    digitalWrite(PERSON_GREEN, HIGH);  // Turn on pedestrian green light
    digitalWrite(PERSON_RED, LOW);     // Turn off pedestrian red light

    // Turn off car lights
    digitalWrite(CAR_GREEN_PIN, LOW);  // Turn off car green light
    digitalWrite(CAR_RED_PIN, HIGH);   // Turn on car red light
    digitalWrite(CAR_YELLOW_PIN, LOW);   // Turn off car yellow light
    delay(2000);
  }
  else if (car_count > person_count) {
    // If there are more cars than people, set car light to green
    digitalWrite(CAR_GREEN_PIN, HIGH); // Turn on car green light
    digitalWrite(CAR_RED_PIN, LOW);    // Turn off car red light
    digitalWrite(CAR_YELLOW_PIN, LOW);   // Turn off car yellow light

    // Turn off pedestrian lights
    digitalWrite(PERSON_GREEN, LOW);   // Turn off pedestrian green light
    digitalWrite(PERSON_RED, HIGH);    // Turn on pedestrian red light
  }
  else if(person_count == 0){
    digitalWrite(CAR_GREEN_PIN, HIGH);  // Turn off car green light
    digitalWrite(CAR_RED_PIN, LOW);   // Turn on car red light
    digitalWrite(CAR_YELLOW_PIN, LOW);   // Turn off car yellow light

    digitalWrite(PERSON_GREEN, LOW);   // Turn off pedestrian green light
    digitalWrite(PERSON_RED, HIGH);    // Turn on pedestrian red light
  }
  else {
    // If the counts are the same, operate normally with red lights for both
    digitalWrite(CAR_GREEN_PIN, LOW);  // Turn off car green light
    digitalWrite(CAR_RED_PIN, HIGH);   // Turn on car red light
    digitalWrite(CAR_YELLOW_PIN, LOW);   // Turn off car yellow light

    digitalWrite(PERSON_GREEN, HIGH);   // Turn off pedestrian green light
    digitalWrite(PERSON_RED, LOW);    // Turn on pedestrian red light
  }

  

  // Add a small delay to avoid overwhelming the system
  delay(1000);
}