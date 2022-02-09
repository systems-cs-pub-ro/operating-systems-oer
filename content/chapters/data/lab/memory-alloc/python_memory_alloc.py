class AttackOnTitanCharacter:
    # constructor
    def __init__(self, id, name):
        self.id = id
        self.name = name

    # toString equivalent
    def __repr__(self):
        return "[id: " + str(self.id) + ", name: " + self.name + "]"

    # destructor
    def __del__(self):
        print("destroying " + self.name)

list = []
list.append(AttackOnTitanCharacter(1, "Eren"))
list.append(AttackOnTitanCharacter(2, "Zeke"))
list.append(AttackOnTitanCharacter(3, "Kenny"))
list.append(AttackOnTitanCharacter(4, "Reiner"))
list.append(AttackOnTitanCharacter(5, "Armin"))
list.append(AttackOnTitanCharacter(6, "Hange"))
list.append(AttackOnTitanCharacter(7, "Levi"))
list.append(AttackOnTitanCharacter(8, "Mikasa"))
list.append(AttackOnTitanCharacter(9, "Sasha"))
list.append(AttackOnTitanCharacter(10, "Erwin"))

print(list)


