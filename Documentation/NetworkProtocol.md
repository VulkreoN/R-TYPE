# Network Protocol

This document presents the network protocol used to communicate for the R-Type project made by the
team `Le groupe qui dort pas pendant 2 mois`. The communication is between a server and several
clients, and there are slight differences between messages sent by the server and ones sent by the
clients. The messages are nevertheless in a similar way, this is how:

## General Message layout:

A message starts with a header and is followed by additional data if it is necessary. The protocol is
binary; therefore, this header has a datatype protocol::Header. Here are examples of messages:

The “|” character will be used to separate data; it can be interpreted as “followed by
***

```
(protocol::Header) PING | NULL
```
Here, no data is sent after the header, we are just sending a ping.
***
```
(protocol::Header) EVENT | (bool) 1 | (int) 20
```
Here, we send an event as seen in the header as well as information about said event after the header.
***

### **Now we will divide this documentation by messages sent by the server and messages sent by the client:**

***

## Messages sent by the server:

### **PING:**
#### **If the server isn’t doing anything, it will default to pinging all of its clients:**

```
(protocol::Header) PING | NULL
```
<br>

### **Game Info:**
#### **If the server is in game mode, it will send a lot of game information:**
```
(protocol::Header) GAME_INFO | player data* | projectile data* | enemy data* | NULL
```
#### The data* sent is as follows for each entity:
```
(int) entity type | (float) x coordinate | (float) y coordinate | (int) ID | (uint8_t) status
```
This is sent for each player, projectile and enemy.

<u>**Entity type**</u> is a number (int) that represents what kind of entity it is (a turret, a spaceship, a fire ball, etc...).

<u>**X and Y coordinates**</u> are the entity’s current whereabouts of the map.

<u>**ID**</u> is the entity’s ID number that represents it and allows us to know what entity it is.

<u>**Status**</u> helps us know if the enemy is alive or dead.

***

## Messages sent by the client:

### **PING:**
#### If the client isn’t doing anything, it will default to pinging the server:

```
(protocol::Header) PING | NULL
```

### **Event**:
#### If the client is playing the game, it sends changes in keyboard keys and mouse to the server as so:
#### For keyboard events:
```
(protocol::Header) EVENT | (bool) is key | (int) button | (uint8_t) state | NULL
```

#### For mouse events:
```
(protocol::Header) EVENT | (bool) is key | (int) button | (uint8_t) state | (int) x coordinate | (int) y coordinate | NULL
````

<u>**Is key**</u> is true if it is a keyboard event, if it’s not a keyboard event, it is false.
<u>**Button**</u> is a number (int) that tells us what button changed.
<u>**State**</u> is the button’s new state (pressed / released).
<u>**X and Y coordinates**</u> are the mouse’s coordinates at the time of the event.
