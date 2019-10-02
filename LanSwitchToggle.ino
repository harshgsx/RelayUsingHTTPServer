#include<SPI.h>
#include<Ethernet.h>



//const int PowerButtonPin = 3;
//const int RestartButtonPin = 4;

const int PowerRelayTriggerPin = 7;
//const int RestartRelayTriggerPin = 8;

//const int LEDPin = 13;


//int PowerButtonState = 0;
int RelayButtonState = 0;

static byte mac[] = { 0xDE,0xAD, 0xBE, 0xEF, 0xFE, 0xED };
static byte ip[] = { 192, 168, 0, 103};
static byte gateway[] = { 192, 168, 0, 1};
static byte subnet[] = { 255, 255, 255, 0};

String ReadString;

EthernetServer server(80);

void setup()
{

    pinMode(PowerRelayTriggerPin, OUTPUT);
    Ethernet.begin(mac, ip, gateway, subnet);
    server.begin();

    Serial.begin(9600);
    Serial.println(Ethernet.localIP());
   
}

void loop()
{

  EthernetClient client = server.available();

//  PowerButtonState = digitalRead(PowerButtonPin);
//  RelayButtonState = digitalRead(RestartButtonPin);
  
  if(client)
  {
    while(client.connected()) 
    {
      if (client.available())
      {
          char c = client.read();

          if(ReadString.length() < 100) 
          {
            ReadString += c;
          }

          if (c == '\n')
          {
            Serial.println(ReadString);
            client.println("HTTP/1.1 200 OK");
           client.println("Content-Type: text/html");
           client.println();     
           client.println("<HTML>");
           client.println("<HEAD>");
           client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
           client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
           client.println("<link rel='stylesheet' type='text/css' link  href='https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css' />");
           
           client.println("<TITLE>Switch Board</TITLE>");
           client.println("</HEAD>");
           client.println("<BODY class=\"container jumbotron\">");
           client.println("<H1 class=\"font-weight-bold\" >SwitchBoard</H1>");
           client.println("<br />");  
           client.println("<hr />");  
           client.println("<a class=\"col col-lg-2 btn btn-success btn-lg btn-primary\" href=\"/?start\"\">Power</a>");
           client.println("<br />");     
           client.println("<br />"); 
           client.println("<br />"); 
           client.println("</BODY>");
           client.println("</HTML>");

     
           delay(1);

           client.stop();
           if (ReadString.indexOf("?start") >0)
           {
            //perform toggle funcion hrtr
              if(digitalRead(PowerRelayTriggerPin) == HIGH)
              {
                  digitalWrite(PowerRelayTriggerPin, LOW);
              }
              else
              {
                   digitalWrite(PowerRelayTriggerPin, HIGH);
              }
           }
           
           
           ReadString="";
          }
      }
    }
  }


}
