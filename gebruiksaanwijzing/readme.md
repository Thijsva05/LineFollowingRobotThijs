# Gebruiksaanwijzing

### opladen / vervangen batterijen
De batterijen moeten worden opgeladen in de apart voorziene lader. Door de elastiek te verwijderen die de batterijhouder van de linefollower op zijn plaats houdt, kunnen de batterijen er makkelijk worden uitgehaald. De batterijen zijn volledig opgeladen wanneer het lichtgevende icoontje groen is, rood betekent dat ze niet volledig zijn opgeladen.

### draadloze communicatie
#### verbinding maken
De linefollower wordt draadloos bestuurd via bluetooth met een smarthpone. De meest geschikte app hiervoor heet: 'Serial Bluetooth Terminal'. Hiermee kan er seriëel worden gecommuniceerd tussen de linefollower en de smartphone. Om een eerste keer een verbinding te maken moet de bluetooth module worden gekoppeld aan de smartphone via de bluetooth instellingen op de smartphone. Er zal ook worden gevraagd om een code in te vullen deze is 12345. Eens dit gebeurt is dient er nog in de app op het connectie icoontje te worden gedrukt, om de app verbinding te laten maken met de linefollower. Wanneer dit gelukt is zal er een bevestiginsbericht verschijnen op de monitor van de app. 

#### commando's
debug [on/off]: toont de huide waarde/status van alle parameters
start: de robot zal starten 
stop: de robot zal stoppen  
set cycle [µs]: looptijd van één enkele cyclus instellen  
set power [0..255]: vermogen instellen dat naar de motors gaat  
set diff [0..1]: instellen hoe groot het verschil in rotatiesnelheid mag zijn tussen de 2 motors bij een bocht  
set kp [0..]: proportionele regelaar  
set ki [0..]: integrerende regelaar  
set kd [0..]: differentiërende regelaar  
calibrate black: zwartwaardes kalibreren  
calibrate white: witwaardes kalibreren  

Een handige tip is om in de app shortcuts in te stellen die deze commando's automatisch invoeren. Deze staan onderaan net boven de typbalk en kunnen worden ingesteld door lang in te houden. Dit bespaard veel tijd.

### kalibratie
Om een goede werking van de robot te garanderen moeten bij elk nieuw gebruik de sensorwaardes voor zwart en wit worden gekalibreerd. Dit omdat er tal van factoren zijn die deze waarden beïnvloeden (lichtsterkte, schaduw...). Dit wordt gerealiseerd door in de bluetooth terminal app 'calibrate black' en 'calibrate white' in te voeren. Belangrijk is dat de sensor bij het kalibreren van de zwarte waardes op een volledig zwart vlak staat, bij de witte waardes op een volledig wit vlak.

### settings
De robot rijdt stabiel met volgende parameters: 
cycle time: 10000
power: 100
Kp: 9.00
Ki: 0.00
Kd: 0.00

### start/stop button
De start/stop knop bevindt zich bovenaan op het zwarte breadboard aan de linkerkant. Wanneer deze bij stilstand éénmaal wordt ingedrukt zal de robot beginnen zoeken naar een lijn. Wanneer deze nu nog eens wordt bedient zal de robot meteen stoppen, enzovoort.
