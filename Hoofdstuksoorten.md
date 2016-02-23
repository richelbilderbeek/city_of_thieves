# Hoofdstuksoorten

### 0: Verhaalbestand

Een bestand waarin een tekst wordt getoond en de speler kan kiezen uit meerdere opties:

```
[tekst]
@0
@[optie]:[hoodstuk]
```

 * [tekst]: de tekst die getoond wordt
 * `0`: code van een verhaalbestand
 * [optie]: de optie de de speler kiest, bijvoorbeeld `1`. Ook is het mogelijk om een optie optioneel te maken, bijvoorbeeld `1?I03`. Dit betekend: Heb je voorwerp `03`, dan kun je optie 1 kiezen. Dit kan ook voor goud: bijvoorbeeld `2?G10` zegt: heb je minstens tien goudstukken, dan kun je optie 2 kiezen.
 * [hoofdstuk]: het hoofstuk waar de speler dan heen gaat

Voorbeeld van verhaalbestanden zijn:

 * [1](Bestanden/1.txt) (simpel)
 * [3](Bestanden/3.txt) (goud nodig voor optie)
 * [35](Bestanden/35.txt) (voorwerp nodig voor optie)

### 1: Test-Je-Geluk 

Een bestand waarin een tekst wordt getoond, het geluk wordt getest, 
en er een tekst is bij pech of geluk en een hoofdstuk erna.

```
[tekst]
@1
@0:[tekst bij pech]@[wat bij pech]
@1:[tekst bij geluk]@[wat bij geluk]
```

 * [tekst]: de tekst die getoond wordt
 * `1`: code van een Test-Je-Geluk
 * [tekst]: de tekst tot het geluk bepaald wordt
 * [tekst bij pech]: de tekst die de speler ziet bij pech
 * [wat bij pech]: wijziging van status en het hoofstuk waar de speler heen gaat bij pech. Bijvoorbeeld `@1` (ga naar hoofdstuk 1) of `@S-1,123` (Stamina min een, ga dan naar hoofdstuk 123)
 * [tekst bij geluk]: de tekst die de speler ziet bij geluk
 * [wat bij geluk]: het hoofstuk waar de speler heen gaat bij geluk

Voorbeeld van een 'Test-Je-Geluk' hoofdstukken zijn

  * [15](Bestanden/15.txt) (simpel)
  * [49](Bestanden/49.txt) (simpel)
  * [64](Bestanden/64.txt) (wijziging status bij pech)

### 2: Test-Je-Behendigheid

Een bestand waarin een tekst wordt getoond, de behendigheid wordt getest, 
en er een tekst is bij geen behendigheid of wel behendigheid en een hoofdstuk erna.

```
[tekst]
@2
@0:[tekst bij geen behendigheid]@[hoodstuk bij geen behendigheid]
@0:[tekst bij wel behendigheid]@[hoodstuk bij wel behendigheid]
```

 * [tekst]: de tekst die getoond wordt
 * `2`: code van een Test-Je-Behendigheid
 * [tekst bij geen behendigheid]: de tekst die de speler ziet bij pech
 * [hoodstuk bij pech]: het hoofstuk waar de speler heen gaat bij pech
 * [tekst bij geluk]: de tekst die de speler ziet bij geluk
 * [hoodstuk bij geluk]: het hoofstuk waar de speler heen gaat bij geluk

Een voorbeeld van een Test-Je-Behendigheid is [69](Bestanden/69.txt).

### 3: Wijziging van je status

Een bestand waarin een tekst wordt getoond en een status (conditie, behendigheid of geluk) wordt gewijzigd

```
[tekst]
@3
@[wat][plus of min][getal]
@[volgende hoofdstuk]
```

 * [tekst]: de tekst die getoond wordt
 * `3`: code van een wijziging van je status
 * [tekst]: de tekst die getoond wordt
 * [wat]: de status die gewijzigd wordt: `D` = Behendigheid ('Dexterity'), `G` = Goud ('Gold'), `S` = Conditie ('Stamina'), `L` = Geluk ('Luck'), `I` = Voorwerp ('Item')
* [plus of min]: is of `+` of `-`
* [getal]: getal die aangeeft hoeveel de status veranderd
* [volgende hoofdstuk]: het nummer van het volgende hoofdstuk

Het [wat] gedeelte is wat ingewikkelder. Er kunnen meerdere dingen gebeuren, deze worden gescheiden met een komma. Ook kan er een vraag in gesteld worden ('Bezit je een malienkolder?') met een vraagteken. Ook kunnen er voorwerpen verloren worden

Enkele voorbeelden van [wat]:

 * `@0`: geen wijziging
 * `@D-1`: verlies 1 behendigheid
 * `@G+10`: krijg 10 goud
 * `@D-1,S-1`: verlies 1 behendigheid en een conditie
 * `@I01-`: verlies het schild 
 * `@I02+`: verkrijg de malienkolder
 * `@I02?D-2`: heb je een malienkolder, verlies dan twee behendigheidpunten
 * `@I02?I02-`: heb je een malienkolder, verlies dan je malienkolder
 * `@I02?D-2,@I02?I02-`: heb je een malienkolder, verlies dan twee behendigheidpunten en je malienkolder

Een voorbeeld van een Wijziging van je status is

 * [8](Bestanden/8.txt)
 * [11](Bestanden/11.txt)

Zie [nummers van de voorwerpen](Voorwerpnummers.md) voor de nummers van de voorwerpen.

### 4: Gevecht binnen een paar beurten

```
[tekst]
@4
@[naam monster(s)]
@[behendigheid]
@[conditie]
@[aantal rondes voordat je onderbroken wordt]
@[hoofdstuk bij onderbreking]
@[hoofdstuk bij klaar voor voor onderbreking]
```

 * [tekst]: de tekst die getoond wordt
 * `4`: code van dit soort hoofdstuk
 * [naam monster(s)]: naam of namen van monsters, bijvoorbeeld `Kobold` of `Eerste Kobold, Tweede Kobold`
 * [behendigheid monster(s): behendigheid monster(s), bijvoorbeeld `7` of `8,9`
 * [conditie monster(s)]: conditie monster(s), bijvoorbeeld `7` of `8,9`
 * [aantal rondes voordat je onderbroken wordt]: aantal rondes voordat het gevecht onderbroken wordt, bijvoorbeeld `6`
 * [hoofdstuk bij onderbreking]: hoofdstuk 
 * [hoofdstuk bij klaar voor voor onderbreking]

Een voorbeeld van een Gevecht binnen een paar beurten is 
  * [10](Bestanden/10.txt): een vijand

### 5: Game over

```
[tekst]
@5
```

Een voorbeeld van een 'Game over' is [9](Bestanden/9.txt)

### 6: Heb je een voorwerp?

Een bestand waarin een tekst wordt getoond en afhankelijk
van het bezit van een voorwerp naar een ander hoofdstuk 
wordt gegaan.

De speler wordt niet om een keuze gevraagd.


```
[tekst]
@6
@I[voorwerpnummer]
@0:[hoofdstuk bij niet bezitten van voorwerp]
@1:[hoofdstuk bij wel bezitten van voorwerp]

```

 * [tekst]: de tekst die getoond wordt
 * `6`: code van een 'Heb je een voorwerp?' hoofdstuk
 * [voorwerpnummer]: het nummer van het voorwerp. Meerdere voorwerpen is ook mogelijk: `@I01,I02`
 * [hoofdstuk bij niet bezitten van voorwerp]: hoofdstuk waar je heen gaat als je het voorwerp niet hebt
 * [hoofdstuk bij wel bezitten van voorwerp]: hoofdstuk waar je heen gaat als je het voorwerp wel hebt

Een voorbeeld van een 'Heb je een voorwerp?' is

 * [14](Bestanden/14.txt)
 * [108](Files/108.txt) (alle voorwerpen om Zanbar Been te verslaan?)

Zie [nummers van de voorwerpen](Voorwerpnummers.md) voor de nummers van de voorwerpen.

### 7: Gevecht

Per monster is er een `Monster` regel.

```
[tekst]
@7
Monster [naam monster] [behendigheid monster] [conditie monster]
Escape [aantal ronden voor je mag ontsnappen] [hoofdstuk bij vluchten]
Next_chapter [hoofdstuk erna bij gewonnen]
```

 * [tekst]: de tekst die getoond wordt
 * `7`: code van dit soort hoofdstuk
 * [naam monster]: naam van monster zonder spaties, bijvoorbeeld `Eerste_kobold`
 * [behendigheid monster]: behendigheid monster, bijvoorbeeld `7`
 * [conditie monster]: conditie monster, bijvoorbeeld `7`
 * [hoofdstuk erna bij gewonnen]

Een voorbeeld van een Gevecht is 
  * [5](Bestanden/5.txt): een vijand
  * [22](Bestanden/22.txt): twee vijanden

### 8: Wijziging status en opties

De status van de speler veranderd, dan wordt de speler om een keuze gevraagd.

```
[tekst]
@8
@[wat][plus of min][getal]
@[optie volgende hoofdstuk]
```

 * [tekst]: de tekst die getoond wordt
 * `8`: code van een verhaal wijziging van je status
 * [tekst]: de tekst die getoond wordt
 * [wat]: de status die gewijzigd wordt: `D` = Behendigheid ('Dexterity'), `S` = Conditie ('Stamina'), `L` = Geluk ('Luck'), `I` = Voorwerp ('Item')
 * [plus of min]: is of `+` of `-`
 * [getal]: getal die aangeeft hoeveel de status veranderd. 
    * Het getal `997` betekent '3x een willekeurig getal van 1 tot en met 6 (oftewel een getal van 3 tot met 18)'
    * Het getal `998` betekent 'alles'
    * Het getal `999` betekent 'een willekeurig getal van 1 tot en met 6'
 * [optie]: de optie de de speler kiest, bijvoorbeeld `1`
 * [hoofdstuk]: het hoofstuk waar de speler dan heen gaat

Het [wat] gedeelte is wat ingewikkelder. Er kunnen meerdere dingen gebeuren, deze worden gescheiden met een komma. Ook kan er een vraag in gesteld worden ('Bezit je een malienkolder?') met een vraagteken. Ook kunnen er voorwerpen verloren worden

Enkele voorbeelden van [wat]:

 * `@D-1`: verlies 1 behendigheid
 * `@D-1,S-1`: verlies 1 behendigheid en een conditie
 * `@I01-`: verlies het schild 
 * `@I02+`: verkrijg de malienkolder
 * `@I02?D-2`: heb je een malienkolder, verlies dan twee behendigheidpunten
 * `@I02?I02-`: heb je een malienkolder, verlies dan je malienkolder
 * `@I02?D-2,@I02?I02-`: heb je een malienkolder, verlies dan twee behendigheidpunten en je malienkolder

Een voorbeeld van een Wijziging van je status is

 * [35](Files/35.txt)
 * [83](Files/83.txt): Conditie gaat omhoog met 1-6 punten

Zie [nummers van de voorwerpen](Voorwerpnummers.md) voor de nummers van de voorwerpen.

### 9: Winkel om spullen te kopen

De speler kan met genoeg goud meerdere voorwerpen kopen.

```
[tekst]
@9
@I[voorwerpnummer]?[prijs],
@[volgende hoofdstuk]:[tekst bij verlaten]
```

 * [tekst]: de tekst die getoond wordt
 * `9`: code van een winkel hoofdstuk
 * [voorwerpnummer]: [nummer van het voorwerp](Voorwerpnummers.md)
 * [prijs]: prijs van het voorwerp in goudstukken
 * [volgende hoofdstuk]: het hoofstuk waar de speler dan heen gaat als hij/zij de winkel verlaat
 * [tekst bij verlaten]: de tekst die wordt getoond als de speler de winkel verlaat

Een voorbeeld van winkel is:

 * [36](Files/36.txt)

Zie [nummers van de voorwerpen](Voorwerpnummers.md) voor de nummers van de voorwerpen.

### 10: Gevecht tegen twee monsters tegelijk

```
[tekst]
@10
Fight_both
Monster [naam monster 1] [behendigheid monster 1] [conditie monster 1] [aanvalskracht monster 1]
Monster [naam monster 2] [behendigheid monster 2] [conditie monster 2] [aanvalskracht monster 2]
Next_chapter [hoofdstuk erna bij gewonnen]
```

 * [tekst]: de tekst die getoond wordt
 * `10`: code van dit soort hoofdstuk
 * [naam monster]: naam van monsters, bijvoorbeeld `Eerste_kobold`
 * [behendigheid monster]: behendigheid monster(s), bijvoorbeeld `7`
 * [conditie monster]: conditie monster, bijvoorbeeld `7`
 * [aanvalskracht monster]: aanvalskracht monster(s), standaard `2`
 * [hoofdstuk erna bij gewonnen]

Een voorbeeld van een Gevecht tegen twee monsters tegelijk
  * [405](Files/405.txt): twee stadswachten

### 11: Game won

```
[tekst]
@11
```

Een voorbeeld van een 'Game won' is [400](Files/400.txt)

### 12: Gevecht met willekeurig monster

```
[tekst]
@12
@[hoofdstuk erna bij gewonnen]
@[hoofdstuk erna bij gewonnen van sterkste monster]
```

 * [tekst]: de tekst die getoond wordt
 * `12`: code van dit soort hoofdstuk
 * [hoofdstuk erna bij gewonnen]
 * [hoofdstuk erna bij gewonnen van aapmens]

Een voorbeeld van een Gevecht is 
  * [201](Files/201.txt): een vijand


### 13: Winkel om spullen te verkopen

De speler kan met genoeg goud meerdere voorwerpen kopen.

```
[tekst]
@9
@I[voorwerpnummer]?[prijs],
@[volgende hoofdstuk]:[tekst bij verlaten]
```

 * [tekst]: de tekst die getoond wordt
 * `13`: code van een winkel hoofdstuk
 * [voorwerpnummer]: [nummer van het voorwerp](Voorwerpnummers.md)
 * [prijs]: prijs van het voorwerp in goudstukken
 * [volgende hoofdstuk]: het hoofstuk waar de speler dan heen gaat als hij/zij de winkel verlaat
 * [tekst bij verlaten]: de tekst die wordt getoond als de speler de winkel verlaat

Een voorbeeld van winkel is:

 * [354](Files/354.txt)

Zie [nummers van de voorwerpen](Voorwerpnummers.md) voor de nummers van de voorwerpen.
