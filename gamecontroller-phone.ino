
// Variables for the Listener
const int ListenerPin = 8; // The pin on the arduino board that this wire is connected to
int listenerState = 0; // To keep track of the opening and closing of the circuit

// Variables for the Tapper
const int tapperPin = 7; // The pin on the arduino board that this wire is connected to
int tapperState = 0; // To keep track of the opening and closing of the circuit
int tapperCount = 0; // To keep track of how often a tapper has reopened

// Generic message variable I can write to
String message = "";

// This function runs once, when your Arduino starts up with your app
void setup() {
	// The pinMode functions below tell Arduino to listen on the pins, rather than use the pins for writing.
	pinMode( ListenerPin, INPUT );
	pinMode( tapperPin, INPUT );
	
	Serial.begin(9600); // Serial allows me to log out messages back to my laptop. It needs to be started here.
}


// Everything in the loop function runs continuously-- it's the heartbeat of your app
void loop() {
	int newListenerState = digitalRead(ListenerPin); // Get the state of the Listener pin
	
	// LISTENER MANAGEMENT
	// if the Listener state changes from its previous state, we should turn on or off Tapper listening functionality
	if( listenerState != newListenerState ){
		listenerState = newListenerState;
		if( listenerState == 1 ){
			Serial.println("Now Lisening for Tapper entries!"); // Just here so I can see it happen
		}else{
			// Once the Listener closes, we should see how many tappers were recorded. We record Tappers in the Tapper Management block later 
			Serial.println("No longer Lisening for Tapper entries.");
			message = "Dialling ";
			message += tapperCount;
			tapperCount = 0; // reset the Tapper count for the next time
			Serial.println(message);
		}
	}

	// TAPPER MANAGEMENT
	int newTapperState = digitalRead(tapperPin);
	if( tapperState != newTapperState ){ // If the tapper state has changed
		tapperState = newTapperState;
		if(listenerState == 1 && tapperState == 0){ // If the tapper has closed, and the Listener is listening
			tapperCount ++;
			message = "Tapper count: ";
			message += tapperCount;
			Serial.println(message);
		}
	}
}


