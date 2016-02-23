# Hoe gebruik ik git en GitHub?

[Hoe gebruik ik git en GitHub?](HoeGebruikIkGitEnGitHub.md)

Volg de eerste keer de volgende stappen:

 1. Installeer git
 2. Download de GitHub naar je harde schijf
 3. Wijzig de code
 4. Benoem de wijzigingen
 5. Download de nieuwste versie van de GitHub
 6. Upload de verbeterde code
 7. Ga naar stap 3

Start de keer erop eenmalig stap 5, start dan bij 3.

## 1. Installeer git

 * Windows en Mac: download Git Bash via `httsp://git-scm.com/downloads`, dat installeren
 * Linux: in terminal: `sudo apt-get install git`

## 2. Download de GitHub naar je harde schijf

Start Git Bash (Windows en Mac) of een terminal (Linux). Type dan:

```
git clone https://github.com/richelbilderbeek/HetRoversnest
```

## 3. Wijzig de code

Pas de code aan.

## 4. Benoem de wijzigingen

Start Git Bash (Windows en Mac) of een terminal (Linux). 

Ga in de folder van de GitHub, bijvoorbeeld:

```
cd HetRoversnest
```

dan:

```
git add --all :/
```

en

```
git commit -m "Hoofdstukken toevoegd"
```

Gefeliciteerd! Je hebt je eerste commit gemaakt!

## 5. Download de nieuwste versie van de GitHub

Voor je de benoemde wijzigingen gaat uploaden is het een goed idee eerst de GitHub te updaten:

Start Git Bash (Windows en Mac) of een terminal (Linux). 

Ga in de folder van de GitHub.

Doe dan:

```
git pull
```

## 6. Upload de verbeterde code

Start Git Bash (Windows en Mac) of een terminal (Linux). Ga in de folder van de GitHub.

Doe dan:

```
git push
```

Nu wordt jouw naam en wachtwoord gevraagd. Als je je wachtwoord intypt zul je geen tekens zien verschijnen.

Gefeliciteerd! Je hebt je eerste commit geupload!