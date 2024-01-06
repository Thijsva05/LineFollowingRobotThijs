# Instructable

Een instructable is een stappenplan - zonder verdere uitleg - hoe je vertrekkend van de bill of materials en gebruik makend van de technische tekeningen de robot kan nabouwen. Ook de nodige stappen om de microcontroller te compileren en te uploaden staan beschreven.  

![Exploded_view](https://github.com/Thijsva05/LineFollowingRobotThijs/assets/146442788/5bdf6431-74d1-477d-afb0-fac5c3af277e)


### stap 1
Bestel alle componenten uit de bill of materials.  

### stap 2
De basis wordt gevormd door een plaatje/dekseltje van harde plastic [2]. De afmetingen hiervan moeten ongeveer 11 x 9 cm bedragen. Belangrijk is dat dit voldoende stevigheid heet om alle componenten te kunnen dragen.

### stap 3
Nu kan de robot worden opgebouwd. Als eerste wordt de sensor [3] gemonteerd. Om deze te bevestigen moeten er 2 gaten van 4 mm worden en geboord. Zorg dat de sensor mooi gecentreerd is. Ook dient er een uitsparing te worden voorzien voor de aansluitpinnen. De sensor wordt bevestigd met twee M3 bouten [5] en moeren [6]. Zorg dat de bouten een gladde, afgeronde kop hebben want hiermee gaat de robot over het parcours glijden. Om eventueel de hoogte van de sensor tegenover het parcours aan te passen kunnen er extra bouten worden toegevoegd tussen bout en basisplaat.

### stap 4
Vervolgens worden de motoren [8] aan weerzijden gemonteerd. Ze worden op hun plaats gehouden doormiddel van bevestigingsbeugels [12]. Deze kunnen worden gemaakt doormiddel van 3D prints, maar een eenvoudige oplossing is om gebruik te maken van LEGO blokjes en plaatjes. Toevallig heeft een blokje dezelfde hoogte als de motor. Door ook nog een plaatje en 2 M4 bouten [13] en moeren [7] langs beide kanten toe te voegen kan de motor zeer goed worden vastgezet. Dit is een belangrijk gegeven om een goede werking van de robot te garanderen.

### stap 5
De wielen [9] kunnen nu ook aan de motoren worden bevestigd. Deze worden simpelweg over de assen van de motoren geschoven.

### stap 6
De Arduino Leonardo [1] wordt net boven de beugels van de motoren geplaatst. Dit doormiddel van 2 lange M4 bouten [4] en moeren. Zorg dat er genoeg ruimte is tussen de sensor en de Arduino om de batterijhouder te zetten. Let ook goed op de oriëntatie van de Arduino zodat de USB-poort bereikbaar blijft! Het gat rechtsachter (van voor gekeken) van de Arduino wordt bevestigd op de bestaande bout van de motor. Dit zal net passen. Boor op basis hiervan de 2 gaten voor de andere bouten.

### stap 7
Op de Arduino Leonardo komt er nog een extra plaatje [14] die het breadboard [15] draagt. Het plaatje wordt gemonteerd op de robot via de 2 diagonale bouten waarop ook de Arduino zit. Het breadboard is voorzien van een kleefstrip, deze kan hiermee op het montageplaatje worden gekleeft. Het plaatje met breadboard moet in principe niet worden vastgezet met moeren, deze zit zo eigenlijk al vast genoeg.

### stap 8
Nu kan de batterijhouder [10] met 2 batterijen [11] worden geplaatst. Om de batterijen in de toekomst makkelijk te kunnen verwijderen moet de houder eenvoudig losgemaakt kunnen worden. Dit door aan beide kanten van de basisplaat een gaatje te boren in de wand op de plaats waar de houder komt. Aan de ene kant komt een elastikje door het gat. Aan de andere kant wordt een klein schroefje voorzien waarachter de elastiek blijft haken. Hierdoor kan de batterijhouder makkelijk worden losgemaakt, maar zit tegelijk ook nog stevig vast.

### stap 9
Vervolgens worden de elektrische componenten op het breadboard geplaatst: H-brug [16], drukknop [18], led en 2 weerstanden (laatste 2 niet op tekening). Ook wordt er nog een schakelaar [19] voorzien achteraan tussen de motoren die de stroombron loskoppelt van de rest van de installatie. Dit kan eenvoudig met een beetje lijm. De HC-05 bluetooth module [17] kan plaatsnemen onder de Arduino en hoeft niet vastgemaakt te worden.

### stap 10
Tot slot moet de elektrische schakeling worden opgebouwd volgens het elektrisch schema. Belangrijk is om zeker alle massa's met elkaar te verbinden en zonder aanwezigheid van de batterijen te werken! Als allerlaatste kan de code worden geupload naar de Arduino via een USB kabel.
