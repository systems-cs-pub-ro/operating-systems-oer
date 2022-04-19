import std.stdio;
import std.format;

enum ON_STACK = 1;
enum N = 10;

class AttackOnTitanCharacter
{
    size_t id;
    string name;

    this(size_t id, string name)
    {
        this.id = id;
        this.name = name;
    }

    override string toString()
    {
        return format("id = %s, name = %s", id, name);
    }

    // destructor - called when object is destroyed
    ~this()
    {
        printf("destroying %s\n", name.ptr);
    }
}

void main()
{
    // allocating on stack
    static if(ON_STACK)
        AttackOnTitanCharacter[N] list;
    // allocating on the heap using dynamic arrays
    else
        AttackOnTitanCharacter[] list = new AttackOnTitanCharacter[N];

    list[0] = new AttackOnTitanCharacter(1, "Eren");
    list[1] = new AttackOnTitanCharacter(2, "Zeke");
    list[2] = new AttackOnTitanCharacter(3, "Kenny");
    list[3] = new AttackOnTitanCharacter(4, "Reiner");
    list[4] = new AttackOnTitanCharacter(5, "Armin");
    list[5] = new AttackOnTitanCharacter(6, "Hange");
    list[6] = new AttackOnTitanCharacter(7, "Levi");
    list[7] = new AttackOnTitanCharacter(8, "Mikasa");
    list[8] = new AttackOnTitanCharacter(9, "Sasha");
    list[9] = new AttackOnTitanCharacter(10, "Erwin");

    writeln(list);

    // no need to free, the garbage collector takes care of everything
}
