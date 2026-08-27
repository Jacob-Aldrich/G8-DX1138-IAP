# README — How to Play

## About the Game

**Among The Survivors** is a single-player survival strategy, resource management and turn-based combat game with psychological horror.

A Skinwalker outbreak has caused society to collapse. Scavenge by day, defend your shelter by night, and decide who is truly human.

Your goal is to keep the player character and as many survivors alive as possible, locate the extraction car, call the helicopter, and survive until evacuation.

---

# Opening Sequence

**This sequence only appears at the start of the game.**

You begin with **5 opportunities** before returning to the house.

You can choose:

**[1]** Search for supplies  
**[2]** Look for survivors  
**[3]** Return to the house

### [1] Search for Supplies

Search for Food and Water.

Each search can find:

* **0–2 Food**
* **0–2 Water**

### [2] Look for Survivors

Search for potential survivors that can be recruited.

You can recruit up to **5 survivors**, for a maximum group of **6 humans including the player**.

Each recruited survivor has randomized:

* **HP:** 80–120
* **Attack:** 2–5

### [3] Return to the House

Return to the house and begin the normal gameplay loop.

---

# Controls

## Exploration

**W** — Move up  
**A** — Move left  
**S** — Move down  
**D** — Move right  
**E** — Interact with nearby objects/objectives  
**B** — Open/Close Outdoor Inventory  
**1–9** — Select numbered actions, party members and combat targets

---

# How to Play

## 1. Begin the Day

After the opening sequence, the normal gameplay loop begins at the house.

You have **5 turns per day**.

At the shelter, you can:

* Eat food
* Drink water
* Manage inventory and equipment
* Make decisions during scenarios
* Choose whether to remain at the shelter or go outside

Inventory and equipment management does **not** consume a turn.

Choosing to go outside commits the remaining day to an expedition.

---

# 2. Manage Resources

The main shared resources are:

* **Food**
* **Water**

Maximum storage:

* **Food: 800**
* **Water: 800**

Each living human loses **33 Hunger** and **33 Thirst** at the end of a day.

If Hunger or Thirst reaches **0**, the character takes **25 HP damage**.

Using:

* **1 Food** restores **25 Hunger**
* **1 Water** restores **25 Thirst**

After survival costs are resolved, living characters recover **20% of maximum HP**, up to their personal maximum.

More survivors provide additional strength and carrying capacity, but also increase daily resource consumption.

---

# 3. Recruit and Manage Survivors

You can have a maximum of **5 recruited survivors**.

The total human group can therefore contain:

**1 Player + 5 Survivors = 6 Humans**

Survivors have their own:

* HP
* Hunger
* Thirst
* Attack
* Equipment

Survivors help increase your combat strength and outdoor carrying capacity.

However, every survivor also consumes food and water.

**Every person you save is another mouth to feed.**

---

# 4. Explore

The outdoor world contains **five 10x10 chunks** arranged in a cross formation.

The player is displayed as:

**P**

### Chunk Layout

```text
                 Chunk 1
                    |
                    |
Chunk 4 --- Chunk 0 (House) --- Chunk 2
                    |
                    |
                 Chunk 3
```

Each chunk can contain up to **6 placed objects**.

Supply objects have a current distribution of:

* **40% Water**
* **40% Food**
* **20% Equipment**

Equipment can spawn as either a **Sword** or **Gun**.

---

# 5. Chunk Transitions

When you cross a valid edge of a chunk, you move into the connected chunk and appear on its opposite edge.

**Objects can block chunk transitions.**

If an object occupies the destination tile, the player cannot enter the chunk through that position.

---

# 6. Outdoor Inventory

The base outdoor inventory has **10 slots**.

Selecting companions for an expedition increases carrying capacity:

* **0 companions:** 10 slots
* **1 companion:** 15 slots
* **2 companions:** 20 slots

The active expedition party can contain:

**1 Player + up to 2 living companions**

Food and Water collected outdoors are transferred into shared shelter storage when returning to the house.

Equipment can be:

* Stored
* Equipped
* Swapped

---

# 7. Equipment

### Sword

* Adds **5 Attack**
* Has no use limit
* Less effective against Skinwalkers
* Deals **0.75× damage** against Skinwalkers

### Gun

* Has **3 instant-defeat shots**
* After those shots are used, Attack becomes **20**
* Highly effective against Skinwalkers
* Deals **1.5× damage** against Skinwalkers

### Unarmed

* Uses the character's base Attack
* Does not consume equipment uses

---

# 8. Scenarios

Scenarios are random events that can occur during eligible shelter turns.

Possible scenarios include:

* A stranger knocking on the door
* A genuine survivor asking for help
* A Skinwalker pretending to be human
* Hostile people attempting to enter the house
* Skinwalkers attacking
* Abandoned supplies or hidden stashes
* Emergency crates
* Door repairs

Scenario choices can:

* Add or remove resources
* Injure or remove survivors
* Damage or repair the door
* Reveal a Skinwalker
* Start combat

Possible decision types include:

* **Send someone**
* **Yes or No**
* **Use an item**
* **Choose someone**

---

# 9. Identifying Skinwalkers

Skinwalkers can imitate human speech and appearance.

They are not always immediately obvious.

Possible clues include:

* Incorrect grammar
* Strange spelling
* Eerie or unnatural dialogue
* Suspicious behaviour
* Contradictory information

These clues are meant to create uncertainty.

**A suspicious person is not necessarily a Skinwalker.**

Trusting the wrong person can cost resources, health or lives.

---

# 10. Combat

Combat is **turn-based**.

Outdoor encounters can create **one or two Skinwalkers**.

The player chooses an action:

**Attack** or **Defend**

### Attack

Choose an enemy target and attack using the character's combat value and equipment.

Damage is affected by:

* Attack value
* Equipment effectiveness
* Random damage variation
* Skinwalker weapon multipliers

Human attacks have a **90%–110% random damage variation**.

### Defend

Defending reduces the next incoming hit by **half**.

### Companions

Living companions take **AI-controlled turns**.

They usually attack the **lowest-health enemy**, but may sometimes defend.

### Enemy Turn

Surviving Skinwalkers can:

* Attack a random living party member
* Defend

Combat continues until one side is defeated.

A character dies when their HP reaches **0 or below**.

Defeated combatants are removed from combat, while surviving characters keep their remaining HP after combat.

---

# 11. Shelter and Door Durability

The house door has a maximum durability of **100**.

* Warning at **40 durability or below**
* Broken at **0 durability**

Scenarios can damage or repair the door.

Keeping the shelter intact is an important part of surviving.

---

# 12. Extraction

The extraction car can become available starting from **Day 3**.

At each later day transition, there is a **30% chance** for the car to become available until it appears.

Once available, the car is placed in a random outer chunk.

Find the car and interact with it to call the helicopter.

After calling the helicopter, you must survive **2 additional days** before evacuation.

---

# 13. Winning

The primary victory condition is the **Helicopter Ending**.

To win:

1. Survive until the extraction car becomes available.
2. Explore the surrounding area and find the car.
3. Interact with the car to call the helicopter.
4. Survive the **2-day helicopter delay**.
5. Reach evacuation.

The ending reports:

* **Days survived**
* **Number of surviving recruited survivors**

---

# 14. Losing

The run ends immediately if the **player character dies**.

Recruited survivors can die without immediately ending the run, but each survivor death reduces:

* Combat strength
* Carrying capacity
* Final survivor count

---

# 15. Military Ending

A **Military Ending** exists as a code path, but it is **not currently connected to the playable progression**.

It is currently a stretch goal and should not be considered a guaranteed ending.

---

# Tips

* Manage Food and Water carefully.
* Use your **5 turns** wisely.
* Going outside commits the remaining day to an expedition.
* Bring companions when their extra carrying capacity and combat strength are worth the resource cost.
* Pay attention to suspicious dialogue and behaviour.
* Don't blindly trust strangers.
* Choose equipment carefully depending on the enemies you expect to face.
* Keep the house door repaired.
* Objects can block your path between chunks.
* Find the extraction car and prepare for the **2-day helicopter countdown**.
* Remember that every survivor you save is another mouth to feed.

**Scavenge by day. Defend your shelter by night. Decide who is truly human.**
