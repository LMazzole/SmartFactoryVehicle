/**
 * @file Communication.cpp
 * @brief Implementation of the Connection class
 *
 * @author Luca Mazzoleni (luca.mazzoleni@hsr.ch)
 *
 * @version 1.0 - added Connection-Implementation - Luca Mazzoleni (luca.mazzoleni@hsr.ch) - 2019-04-16
 *
 * @date 2019-04-09
 * @copyright Copyright (c) 2019
 *
 */

/*
Useful Links
https://techtutorialsx.com/2017/04/29/esp32-sending-json-messages-over-mqtt/
https://randomnerdtutorials.com/decoding-and-encoding-json-with-arduino-or-esp8266/
https://arduinodiy.wordpress.com/2017/07/30/json-mqtt-and-openhab/
https://assetwolf.com/learn/sending-data-from-arduino-to-cloud
*/

#include "Communication.h"

//==Global Vairable====
myJSON _myjson;                                              ///< instance of myJSON
CircularBuffer<myJSONStr, MAX_JSON_MESSAGES_SAVED> _buffer;  ///< instance of CircularBuffer

//======Func====
/**
 * @todo String is inefficient -> change to char array and handle pointer
 * @todo Change global implementation
 */
void callback(char* topic, byte* payload, unsigned int length) {
    DBFUNCCALLln("callback(const char[] topic, byte* payload, unsigned int length)");
    char payload_str[length];
    for (unsigned int i = 0; i < length; i++) {  // iterate message till lentgh caus it's not 0-terminated
        payload_str[i] = (char)payload[i];
    }
    payload_str[length] = '\0';

    String topic_str = String((char*)topic);
    String currentMessage = topic_str + " " + payload_str;
    DBINFO3("CurrMessage: ");
    DBINFO3ln(currentMessage);
    DBINFO3("LastMessage: ");
    DBINFO3ln(_myjson.lastMessage);

    if ((_myjson.lastMessage == currentMessage) && (_buffer.size() != 0)) {
        DBINFO2ln("Duplicated Message");
    } else {
        DBINFO2ln("Add to Buffer");
        //https://stackoverflow.com/questions/1360183/how-do-i-call-a-non-static-method-from-a-static-method-in-c
        myJSONStr newMessage = _myjson.parsingJSONToStruct((char*)payload_str);
        newMessage.topic = topic_str;
        DBINFO3("Topic: ");
        DBINFO3ln(newMessage.topic);
        DBINFO3("Sensor: ");
        DBINFO3ln(newMessage.sensor);
        DBINFO3("Time: ");
        DBINFO3ln(newMessage.time);
        DBINFO3("data_0: ");
        DBINFO3ln(newMessage.data[0]);
        DBINFO3("data_1: ");
        DBINFO3ln(newMessage.data[1]);
        DBINFO3ln(_buffer.size());
        // _myjson.StructIsEqual(newMessage, _buffer.first()); //bug this calls changes the message chars somehow?
        _buffer.unshift(newMessage);
        _myjson.lastMessage = currentMessage;
    }
}

Communication::Communication() {
}
