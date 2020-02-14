# City of Thieves solved

 * Authors: Richel J.C. Bilderbeek [1], Rafayel Garishyan [2], Rob Krueger [2], 
   Rijk van Putten [2]

 * [1] Corresponding author
 * [2] Contributed to the work equally

## Abstract

City of Thieves is a text adventure in the form of a book.
To beat it, a player has to make the right choices, in a stochastic environment.
The optimal strategy to beat this game is unknown.
Here we show the optimal strategy to beat this game.
[prime result here].

## Introduction

In the 1980's, before the era of computing, adventure books
allowed the reader to partake a fictional adventure.
Adventure books consisted of hundreds of short chapters in
a random order. The reader starts at chapter 1 and is asked
to do one of multiple actions. Each action takes the player
to a next chapter. The player ultimately completes the game
or dies.

City of Thieves is a an adventure book written by Ian Livingstone in 1984.
The player should venture to the castle of the protagonist,
after having visited a certain person in a medieval city,
the titular 'City of Thieves'. 

A character has three statistics: health, skill and luck. 
More health allows a player to take more damage,
for example, taking hits in combat.
More skill allows a player to be better in combat,
as well as succeed in certain situations, 
for example, [example].
More luck allows a player in a situation that requires luck,
for example, when an arrow trap springs, luck may let the player 
avoid the (lethal!) arrow.

These three statistics can be modified within the game.
Health can be increased by certain items, such as food. 
Health decreases when taking damage, which is usually in combat,
but can also stem from other physical injuries, such as falling down a wall.
Skill can be increased by certain items, such as a better sword.
Skill can be decreased by other such items, such as cursed gloves that
decrease the dexterity of the wearer.
Luck can be increased by certain events or items, 
such as hearing a blessed song.
Luck decreases mostly by using it (see below) or by certain events, such as 
killing one of the key characters.

The game starts with a character generation session, 
similar to most RPGs. [elaborate on exact process, with dice rolls etc.].
According to Livingstone, the adventure is constructed

After the character generation session, a player may pick
one of three potions, for either of the three statistics.
Where the health and skill potion refresh their respective value
to the initial value, a luck potion does so, as well as add one additional 
point.

At the start of the game, the player starts with [items] and [number] 
gold coins. These items may be lost or sold. 
The gold coins are used as a currency, to buy items or other situations,
such as bribing a guard.

Within the actual game, there are multiple kinds of chapters.
The most common type of chapter is to pick one of multiple
actions. Sometimes some actions can only be picked after having
acquired a certain item [example here]. The other types of chapters
are fighting chapters, logical chapters, luck chapters and skill chapters.

In a fighting chapter, the player fights one, two or three opponents.
All opponents have a know value for their health and skill, that
are similar to the player. The goal of the player, is to 
succeed in combat, by bringing down the health of opponents to zero.
Likewise, when an opponent hits the player, its health goes down,
where a health of zero ends the game. 
A player can use luck to increase the damage dealt to the enemy,
or to decrease the damage dealth by that enemy. Using luck decreases its
value, decreasing the change of a positive event in successive usages. 

A logical chapter is simply a conditional statement
regarding the possession of an item. For example, when the
player leaves the city, he/she needs to possess some key items,
else the game is over.

Luck and skill chapters are similar: a player needs to roll the dice
to test his/her skill or luck, after which a different chapter follows
depending the success of this. An example of a skill chapter is [example].
An example of a luck chapter is [example]. The only additional difference
is that using luck decrease that statistic.

The adventure starts at the gates of the city, the first city
streets, a bridge at which a vital character lives, some more city streets,
after which the city is left. If the player has acquired some esstial items,
the adventure goes through a forest, followed by the keep of the protagonist.
The story always go forwards, that is each location can only be visited once,
as the player cannot venture back.
There is only location (the keep's 2nd and 3rd [check] floor) in which
a location can be visited multiple times, but doing so is either
neutral or detrimental.

Because the player cannot go back and the player needs to acquire some
essential items, some decisions cause the player to lose the game due to
this. For example, at the first junction after crossing the bridge,
the player must go towards the [name] street to acquire such a key item,
after which the game takes the player back to follow the other street 
afterwards. Therefore, reaching the latter location on itself is uninformative:
only with the key item acquired the player has a change of winning the game.
The state transition, however, is informative: going from that 
junction directly to the final destination (without getting the
key item) is a sure fail.

Upon passing the city gate, there is junction, in which the player
has to choose one of three streets. None of these streets contain an
essential item and all lead to the same bridge. Yet, these three routes
vary in the items a player can find as well as the amount of danger.
It is unknown which of these three streets results in the
highest chance of success.

## Hypotheses

 * H_0: it does not matter which of the three streets is picked at the initial
   junction for the chance of winning the game


## Methods

To allow the game to be solved by a computer, it has been converted
to a computer game.

Assigning pay-off values to certain location is expected to fail,
as only a location is uninformative. For example, one can reach a certain
location by taking a short-cut, yet without acquiring an essential item. 

Assigning pay-off values to certain choices is expected to be more 
viable, as this will allow an algorithm to take a detour to obtain
a vital item.

## Conclusions

## Discussions

## Acknowledgements

RJCB was the main writer of the manuscript.
RJCB rewrote the book as a text adventure.
RG, RK, RvP, ... wrote the code for the 'Methods' section.
RJCB co-authored the 'Methods' and 'Conclusion' section with RG, RK and RvP.

## References

 * [Giddings, 2006] Giddings, Seth. Walkthrough: Videogames and technocultural form. Diss. University of the West of England, Bristol, 2006.
 * [Livingstone, 1984] Livingstone, Ian. City of Thieves. No. 5. Dell Pub Co, 1984.

