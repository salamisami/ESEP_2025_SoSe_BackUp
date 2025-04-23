Notizen:
+ Rolle vs Verantwortung unklar z.B. Tester verantwortlich dass das Team auch tests schreibt. 
+ Welches Modell? (V oder Scrum?) -> Heute sollte schon entschieden werden welches Vorgehensmodell wir nutzen sollen -> zu langsam -> Welche Rollen gibt es in Scrum? Welches in V Modell? -> 3 Rollen in Scrum vs ganz viele in V-Modell
+ Frau Dai scheint das Scrum Modell zu favorisieren 
+ Rollen müssen überdacht werden (Scrum, V?)
+ Montag 13-16 Uhr **JOUR FIXED** 
+ Antwort auch geben wenn wir die Antwort nicht wissen
+ Referenzieren lernen
+ Bei manchen Fragen könne wir gerne mit Vorschlägen kommen z.B. Frage bezüglich neues Werkstück eingefügt im Ruhemodus 
	+ Proaktiver werden 
+ Kalibrierungsmodus zwingend notwendig für Nuancen der Anlagen zu erfassen, bitte nur einmal und nicht nach jedem Build neu kalibrieren
+ Enrico empfiehlt sehr den Selbstest -> Sanity check ob die Anlage funktioniert oder nicht (bevor man den Fehler im Code sucht) -> Empfehlung Manuell 
+ In Aufgabenstellung ist die Fehlerbehandlung noch sehr grob -> wir müssen das viel genauer beschreiben
+ Buttons mit Feedback (z.B. LED an wenn Button clickable oder wenn button press registriert geht LED an/aus) -> Solche Dingen sollen im User Manual stehen
+ Userbility und durchsatz
+ System test von abnahmetest und die einzelnen 
+ Systemkontext feingranularer z.B. Schnitstelle gehört nicht dazu, unterteilung zu FB1 und FB2, Sensorik Aktorik, Buttons, Lichtschranke etc
+ Komponentediagramm neu machen -> Interface ist die Bubble (Interface doppelt gemoppelt)
+ Frau Dai holt die Peitsche 
+ Der Kranke muss Attest mitbringen 

| Frage                                                                                                                             | Antwort                                                                                                                              |
| --------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------ |
| - Doppele Bezeichnungen                                                                                                           |                                                                                                                                      |
| - Spannung/ Frequenz für den Antrieb                                                                                              |                                                                                                                                      |
| - Taster LEDs fest verdatet oder Software ?                                                                                       |                                                                                                                                      |
|                                                                                                                                   |                                                                                                                                      |
| - MQTT IP Adresse Passwort etc.                                                                                                   | Kein eigenes Server an der Hochschule                                                                                                |
|                                                                                                                                   |                                                                                                                                      |
| Interaktion zwischen 2 Anlagen <br>(75) Gilt die Bedientaster analysis auch für 2. Anlage?                                        | Gilt für beide, beide haben die Ampel und die Anzeige                                                                                |
| FSM: 1. (84) Was bedeutet Zustand OK genau? Ist dasgleiche wie Ruhe/Bereit?                                                       | Kein weiterer Fehler liegt an                                                                                                        |
| FSM: 2. (88) Wohin geht der Zustand nach dem Verlassen/Quittieren?                                                                | Case: Rutsche geblockt -> windstoß werkstück fällt runter rutsche nichtmehr geblockt -> gegangen unquittiert user kann es quittieren |
| Hoher durchsatz vs nur 1 Werkstück auf Förderband 2                                                                               | Ist so gewollt. In der Rutsche zählt nicht. Förderband 1 soll hohe Produktivität haben                                               |
| Was ist gemeint mit Reisezeit?                                                                                                    | Von der Weiche bis zur Rutsche                                                                                                       |
| Farbe der Werkstücke relevant?                                                                                                    | Nein.                                                                                                                                |
| Was sind defekte/fehlerhafte Werkstücke?                                                                                          | Das ist alles was nicht in die Reihung passt. Unbekannt z.B. Schlüsselbund oder binäres Werkstück,                                   |
| Wie ist der Anfang von Förderbandmodul 1 definiert?                                                                               | Anfang ist vorne links Lichtschranke, frei -> Lichtschranke nichtmehr blockiert                                                      |
| Was sind Typen                                                                                                                    | Die Werkstücke sind die Typen ->                                                                                                     |
| Wann muss der Typ spätestens bekannt sein                                                                                         | Metallsensor -> sollten wir selber beantworten können                                                                                |
| Was ist wenn ein Werkstück hinzugefügt wird, währen sich die Anlage m Ruhemodus befindet?                                         | Fehlerzustand -> wir können nur erkennen dass etwas zu früh ankommt                                                                  |
| Jederzeit möglich in den Service mode? Wenn werkstücke auf dem Förderbandmodul soll es möglich sein in den Service mode zu gehen? | Nur im Ruhemodus Satz $_{64}$                                                                                                        |
|                                                                                                                                   |                                                                                                                                      |

TODO:
+ Vorgehensmodell
+ Rollen
+ ATs besser formulieren z.B. AT-1 Titel User wird getestet nicht die Anlage
+ Abkürzungen bestimmen für Förderbandmodul 1 & 2 und Werkstück 
	+ -> Glossar 