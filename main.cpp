#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#define row 13
#define column 47


#define BASIC {0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36}

// Special
#define SPECIAL {38,40,42,44,46}
#define ADVA {0,1,2,3,4,5,6,7,8}


class Tamil {
private:
    struct Item {
        const char* key;
        const char* val;
    };

    // Transliteration table: two rows (primary and secondary mappings)
    Item table[column][13] = {
        {{"q","ஃ"}, {"a","அ"}, {"aa","ஆ"}, {"i","இ"}, {"ii","ஈ"}, {"u","உ"}, {"uu","ஊ"}, {"e","எ"}, {"ee","ஏ"}, {"ai","ஐ"}, {"o","ஒ"}, {"oo","ஓ"}, {"au","ஔ"}},
        {{"q","ஃ"}, {"",""}, {"A","ஆ"}, {"",""}, {"I","ஈ"}, {"",""}, {"U","ஊ"}, {"",""}, {"E","ஏ"}, {"ai","ஐ"}, {"",""}, {"O","ஓ"}, {"",""}},
        {{"k","க்"},{"ka","க"},{"kaa","கா"},{"ki","கி"},{"kii","கீ"},{"ku","கு"},{"kuu","கூ"},{"ke","கெ"},{"kee","கே"},{"kai","கை"},{"ko","கொ"},{"koo","கோ"},{"kau","கௌ"}},
        {{"k","க்"},{"",""},{"kA","கா"},{"",""},{"kI","கீ"},{"",""},{"kU","கூ"},{"",""},{"kE","கே"},{"",""},{"",""},{"kO","கோ"},{"",""}},
        {{"ng","ங்"},{"nga","ங"},{"ngaa","ஙா"},{"ngi","ஙி"},{"ngii","ஙீ"},{"ngu","ஙு"},{"nguu","ஙூ"},{"nge","ஙெ"},{"ngee","ஙே"},{"ngai","ஙை"},{"ngo","ஙொ"},{"ngoo","ஙோ"},{"ngau","ஙௌ"}},
        {{"ng","ங்"},{"",""},{"ngA","ஙா"},{"",""},{"ngI","ஙீ"},{"",""},{"ngU","ஙூ"},{"",""},{"ngE","ஙே"},{"",""},{"",""},{"ngO","ஙோ"},{"",""}},
        {{"c","ச்"},{"ca","ச"},{"caa","சா"},{"ci","சி"},{"cii","சீ"},{"cu","சு"},{"cuu","சூ"},{"ce","செ"},{"cee","சே"},{"cai","சை"},{"co","சொ"},{"coo","சோ"},{"cau","சௌ"}},
        {{"c","ச்"},{"",""},{"cA","சா"},{"",""},{"cI","சீ"},{"",""},{"cU","சூ"},{"",""},{"cE","சே"},{"",""},{"",""},{"cO","சோ"},{"",""}},
        {{"nj","ஞ்"},{"nja","ஞ"},{"njaa","ஞா"},{"nji","ஞி"},{"njii","ஞீ"},{"nju","ஞு"},{"njuu","ஞூ"},{"nje","ஞெ"},{"njee","ஞே"},{"njai","ஞை"},{"njo","ஞொ"},{"njoo","ஞோ"},{"njau","ஞௌ"}},
        {{"nj","ஞ்"},{"",""},{"njA","ஞா"},{"",""},{"njI","ஞீ"},{"",""},{"njU","ஞூ"},{"",""},{"njE","ஞே"},{"",""},{"",""},{"njO","ஞோ"},{"",""}},
        {{"t","ட்"},{"ta","ட"},{"taa","டா"},{"ti","டி"},{"tii","டீ"},{"tu","டு"},{"tuu","டூ"},{"te","டெ"},{"tee","டே"},{"tai","டை"},{"to","டொ"},{"too","டோ"},{"tau","டௌ"}},
        {{"t","ட்"},{"",""},{"tA","டா"},{"",""},{"tI","டீ"},{"",""},{"tU","டூ"},{"",""},{"tE","டே"},{"",""},{"",""},{"tO","டோ"},{"",""}},
        {{"N","ண்"},{"Na","ண"},{"Naa","ணா"},{"Ni","ணி"},{"Nii","ணீ"},{"Nu","ணு"},{"Nuu","ணூ"},{"Ne","ணெ"},{"Nee","ணே"},{"Nai","ணை"},{"No","ணொ"},{"Noo","ணோ"},{"Nau","ணௌ"}},
        {{"N","ண்"},{"",""},{"NA","ணா"},{"",""},{"NI","ணீ"},{"",""},{"NU","ணூ"},{"",""},{"NE","ணே"},{"",""},{"",""},{"NO","ணோ"},{"",""}},
        {{"th","த்"},{"tha","த"},{"thaa","தா"},{"thi","தி"},{"thii","தீ"},{"thu","து"},{"thuu","தூ"},{"the","தெ"},{"thee","தே"},{"thai","தை"},{"tho","தொ"},{"thoo","தோ"},{"thau","தௌ"}},
        {{"th","த்"},{"",""},{"thA","தா"},{"",""},{"thI","தீ"},{"",""},{"thU","தூ"},{"",""},{"thE","தே"},{"",""},{"",""},{"thO","தோ"},{"",""}},
        {{"w","ந்"},{"wa","ந"},{"waa","நா"},{"wi","நி"},{"wii","நீ"},{"wu","நு"},{"wuu","நூ"},{"we","நெ"},{"wee","நே"},{"wai","நை"},{"wo","நொ"},{"woo","நோ"},{"wau","நௌ"}},
        {{"w","ந்"},{"",""},{"wA","நா"},{"",""},{"wI","நீ"},{"",""},{"wU","நூ"},{"",""},{"wE","நே"},{"",""},{"",""},{"wO","நோ"},{"",""}},
        {{"p","ப்"},{"pa","ப"},{"paa","பா"},{"pi","பி"},{"pii","பீ"},{"pu","பு"},{"puu","பூ"},{"pe","பெ"},{"pee","பே"},{"pai","பை"},{"po","பொ"},{"poo","போ"},{"pau","பௌ"}},
        {{"p","ப்"},{"",""},{"pA","பா"},{"",""},{"pI","பீ"},{"",""},{"pU","பூ"},{"",""},{"pE","பே"},{"",""},{"",""},{"pO","போ"},{"",""}},
        {{"m","ம்"},{"ma","ம"},{"maa","மா"},{"mi","மி"},{"mii","மீ"},{"mu","மு"},{"muu","மூ"},{"me","மெ"},{"mee","மே"},{"mai","மை"},{"mo","மொ"},{"moo","மோ"},{"mau","மௌ"}},
        {{"m","ம்"},{"",""},{"mA","மா"},{"",""},{"mI","மீ"},{"",""},{"mU","மூ"},{"",""},{"mE","மே"},{"",""},{"",""},{"mO","மோ"},{"",""}},
        {{"y","ய்"},{"ya","ய"},{"yaa","யா"},{"yi","யி"},{"yii","யீ"},{"yu","யு"},{"yuu","யூ"},{"ye","யெ"},{"yee","யே"},{"yai","யை"},{"yo","யொ"},{"yoo","யோ"},{"yau","யௌ"}},
        {{"y","ய்"},{"",""},{"yA","யா"},{"",""},{"yI","யீ"},{"",""},{"yU","யூ"},{"",""},{"yE","யே"},{"",""},{"",""},{"yO","யோ"},{"",""}},
        {{"r","ர்"},{"ra","ர"},{"raa","ரா"},{"ri","ரி"},{"rii","ரீ"},{"ru","ரு"},{"ruu","ரூ"},{"re","ரெ"},{"ree","ரே"},{"rai","ரை"},{"ro","ரொ"},{"roo","ரோ"},{"rau","ரௌ"}},
        {{"r","ர்"},{"",""},{"rA","ரா"},{"",""},{"rI","ரீ"},{"",""},{"rU","ரூ"},{"",""},{"rE","ரே"},{"rai","ரை"},{"",""},{"rO","ரோ"},{"",""}},
        {{"l","ல்"},{"la","ல"},{"laa","லா"},{"li","லி"},{"lii","லீ"},{"lu","லு"},{"luu","லூ"},{"le","லெ"},{"lee","லே"},{"lai","லை"},{"lo","லொ"},{"loo","லோ"},{"lau","லௌ"}},
        {{"l","ல்"},{"",""},{"lA","லா"},{"",""},{"lI","லீ"},{"",""},{"lU","லூ"},{"",""},{"lE","லே"},{"",""},{"",""},{"lO","லோ"},{"",""}},
        {{"v","வ்"},{"va","வ"},{"vaa","வா"},{"vi","வி"},{"vii","வீ"},{"vu","வு"},{"vuu","வூ"},{"ve","வெ"},{"vee","வே"},{"vai","வை"},{"vo","வொ"},{"voo","வோ"},{"vau","வௌ"}},
        {{"v","வ்"},{"",""},{"vA","வா"},{"",""},{"vI","வீ"},{"",""},{"vU","வூ"},{"",""},{"vE","வே"},{"",""},{"",""},{"vO","வோ"},{"",""}},
        {{"z","ழ்"},{"za","ழ"},{"zaa","ழா"},{"zi","ழி"},{"zii","ழீ"},{"zu","ழு"},{"zuu","ழூ"},{"ze","ழெ"},{"zee","ழே"},{"zai","ழை"},{"zo","ழொ"},{"zoo","ழோ"},{"zau","ழௌ"}},
        {{"z","ழ்"},{"",""},{"zA","ழா"},{"",""},{"zI","ழீ"},{"",""},{"zU","ழூ"},{"",""},{"zE","ழே"},{"",""},{"",""},{"zO","ழோ"},{"",""}},
        {{"L","ள்"},{"La","ள"},{"Laa","ளா"},{"Li","ளி"},{"Lii","ளீ"},{"Lu","ளு"},{"Luu","ளூ"},{"Le","ளெ"},{"Lee","ளே"},{"Lai","ளை"},{"Lo","ளொ"},{"Loo","ளோ"},{"Lau","ளௌ"}},
        {{"L","ள்"},{"",""},{"LA","ளா"},{"",""},{"LI","ளீ"},{"",""},{"LU","ளூ"},{"",""},{"LE","ளே"},{"",""},{"",""},{"LO","ளோ"},{"",""}},
        {{"R","ற்"},{"Ra","ற"},{"Raa","றா"},{"Ri","றி"},{"Rii","றீ"},{"Ru","று"},{"Ruu","றூ"},{"Re","றெ"},{"Ree","றே"},{"Rai","றை"},{"Ro","றொ"},{"Roo","றோ"},{"Rau","றௌ"}},
        {{"R","ற்"},{"",""},{"RA","றா"},{"",""},{"RI","றீ"},{"",""},{"RU","றூ"},{"",""},{"RE","றே"},{"",""},{"",""},{"RO","றோ"},{"",""}},
        {{"n","ன்"},{"na","ன"},{"naa","னா"},{"ni","னி"},{"nii","னீ"},{"nu","னு"},{"nuu","னூ"},{"ne","னெ"},{"nee","னே"},{"nai","னை"},{"no","னொ"},{"noo","னோ"},{"nau","னௌ"}},
        {{"n","ன்"},{"",""},{"nA","னா"},{"",""},{"nI","னீ"},{"",""},{"nU","னூ"},{"",""},{"nE","னே"},{"",""},{"",""},{"nO","னோ"},{"",""}},
        {{"j","ஜ்"},{"ja","ஜ"},{"jaa","ஜா"},{"ji","ஜி"},{"jii","ஜீ"},{"ju","ஜு"},{"juu","ஜூ"},{"je","ஜெ"},{"jee","ஜே"},{"jai","ஜை"},{"jo","ஜொ"},{"joo","ஜோ"},{"jau","ஜௌ"}},
        {{"j","ஜ்"},{"",""},{"jA","ஜா"},{"",""},{"jI","ஜீ"},{"",""},{"jU","ஜூ"},{"",""},{"jE","ஜே"},{"",""},{"",""},{"jO","ஜோ"},{"",""}},
        {{"sh","ஷ்"},{"sha","ஷ"},{"shaa","ஷா"},{"shi","ஷி"},{"shii","ஷீ"},{"shu","ஷு"},{"shuu","ஷூ"},{"she","ஷெ"},{"shee","ஷே"},{"shai","ஷை"},{"sho","ஷொ"},{"shoo","ஷோ"},{"shau","ஷௌ"}},
        {{"sh","ஷ்"},{"",""},{"shA","ஷா"},{"",""},{"shI","ஷீ"},{"",""},{"shU","ஷூ"},{"",""},{"shE","ஷே"},{"",""},{"",""},{"shO","ஷோ"},{"",""}},
        {{"S","ஸ்"},{"Sa","ஸ"},{"Saa","ஸா"},{"Si","ஸி"},{"Sii","ஸீ"},{"Su","ஸு"},{"Suu","ஸூ"},{"Se","ஸெ"},{"See","ஸே"},{"Sai","ஸை"},{"So","ஸொ"},{"Soo","ஸோ"},{"Sau","ஸௌ"}},
        {{"S","ஸ்"},{"",""},{"SA","ஸா"},{"",""},{"SI","ஸீ"},{"",""},{"SU","ஸூ"},{"",""},{"SE","ஸே"},{"",""},{"",""},{"SO","ஸோ"},{"",""}},
        {{"h","ஹ்"},{"ha","ஹ"},{"haa","ஹா"},{"hi","ஹி"},{"hii","ஹீ"},{"hu","ஹு"},{"huu","ஹூ"},{"he","ஹெ"},{"hee","ஹே"},{"hai","ஹை"},{"ho","ஹொ"},{"hoo","ஹோ"},{"hau","ஹௌ"},},
        {{"h","ஹ்"},{"",""},{"hA","ஹா"},{"",""},{"hI","ஹீ"},{"",""},{"hU","ஹூ"},{"",""},{"hE","ஹே"},{"",""},{"",""},{"hO","ஹோ"},{"",""}},
        {{"ksh","க்ஷ்"},{"ksha","க்ஷ"},{"kshaa","க்ஷா"},{"kshA","க்ஷா"},{"kshi","க்ஷி"},{"sri","ஸ்ரீ"},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""},{"",""}}
    };
// {"",""}
// // EXTRA
//     // ```
//     // //     {"s","ச்"},{"sa","ச"},{"saa","சா"},{"sA","சா"},{"si","சி"},{"sii","சீ"},{"sI","சீ"},{"su","சு"},{"suu","சூ"},{"sU","சூ"},{"se","செ"},{"see","சே"},{"sE","சே"},{"sai","சை"},{"so","சொ"},{"soo","சோ"},{"sO","சோ"},{"sau","சௌ"},
//     //     {"d","ட்"},{"da","ட"},{"daa","டா"},{"dA","டா"},{"di","டி"},{"dii","டீ"},{"dI","டீ"},{"du","டு"},{"duu","டூ"},{"dU","டூ"},{"de","டெ"},{"dee","டே"},{"dE","டே"},{"dai","டை"},{"do","டொ"},{"doo","டோ"},{"dO","டோ"},{"dau","டௌ"},
//         {"n-","ந்"},{"n-a","ந"},{"n-aa","நா"},{"n-A","நா"},{"n-i","நி"},{"n-ii","நீ"},{"n-I","நீ"},{"n-u","நு"},{"n-uu","நூ"},{"n-U","நூ"},{"n-e","நெ"},{"n-ee","நே"},{"n-E","நே"},{"n-ai","நை"},{"n-o","நொ"},{"n-oo","நோ"},{"n-O","நோ"},{"n-au","நௌ"},
//     // ```
        
    // Return the display width of a UTF‑8 string (number of terminal columns)
    // Assumes each code point occupies one column (safe for Tamil characters here).
    int displayWidth(const string& s) const {
        int width = 0;
        size_t i = 0;
        while (i < s.size()) {
            unsigned char c = s[i];
            // Count leading bytes of UTF‑8 sequences (ASCII or multi‑byte)
            if ((c & 0x80) == 0) {          // ASCII
                width++;
                i++;
            } else if ((c & 0xE0) == 0xC0) { // 2‑byte sequence
                width++;
                i += 2;
            } else if ((c & 0xF0) == 0xE0) { // 3‑byte sequence (Tamil chars)
                width++;
                i += 3;
            } else if ((c & 0xF8) == 0xF0) { // 4‑byte sequence
                width++;
                i += 4;
            } else {                          // Invalid continuation byte – treat as one column
                width++;
                i++;
            }
        }
        return width;
    }

    // Print a cell's content padded with spaces to reach 'colWidth' display columns
    void printCell(const string& content, int colWidth) const {
        cout << content;
        int pad = colWidth - displayWidth(content);
        for (int i = 0; i < pad; ++i) cout << ' ';
    }

public:
    void printTable() {
        // 1. Determine the maximum display width among all cells
        int maxWidth = 0;
        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 13; ++c) {
                string content;
                if (table[r][c].key[0] != '\0')   // non‑empty cell
                    content = string(table[r][c].key) + "-" + table[r][c].val;
                // else content stays empty
                int w = displayWidth(content);
                if (w > maxWidth) maxWidth = w;
            }
        }

        // 2. Set a fixed column width (max + 2 for a little breathing space)
        const int colWidth = maxWidth + 3;

        // 3. Print the table with uniform column widths
        for (int r = 0; r < column; ++r) {
            for (int c = 0; c < 13; ++c) {
                string content;
                if (table[r][c].key[0] != '\0')
                    content = string(table[r][c].key) + "-" + table[r][c].val;
                printCell(content, colWidth);
            }
            cout << endl;
        }
    }



    void printSelectedRows() {
        int rows[] = BASIC;
        int rowCount = sizeof(rows)/sizeof(rows[0]);

        int maxWidth = 0;

        // find max width
        for (int i = 0; i < rowCount; i++) {
            int r = rows[i];
            for (int c = 0; c < 13; c++) {
                string content;
                if (table[r][c].key[0] != '\0')
                    content = string(table[r][c].key) + "-" + table[r][c].val;

                int w = displayWidth(content);
                if (w > maxWidth) maxWidth = w;
            }
        }

        const int colWidth = maxWidth + 3;

        // print only selected rows
        for (int i = 0; i < rowCount; i++) {
            int r = rows[i];
            for (int c = 0; c < 13; c++) {
                string content;
                if (table[r][c].key[0] != '\0')
                    content = string(table[r][c].key) + "-" + table[r][c].val;

                printCell(content, colWidth);
            }
            cout << endl;
        }
    }




    void printSelectedRows_S() {
        int rows[] = SPECIAL;
        int rowCount = sizeof(rows)/sizeof(rows[0]);

        int maxWidth = 0;

        // find max width
        for (int i = 0; i < rowCount; i++) {
            int r = rows[i];
            for (int c = 0; c < 13; c++) {
                string content;
                if (table[r][c].key[0] != '\0')
                    content = string(table[r][c].key) + "-" + table[r][c].val;

                int w = displayWidth(content);
                if (w > maxWidth) maxWidth = w;
            }
        }

        const int colWidth = maxWidth + 3;

        // print only selected rows
        for (int i = 0; i < rowCount; i++) {
            int r = rows[i];
            for (int c = 0; c < 13; c++) {
                string content;
                if (table[r][c].key[0] != '\0')
                    content = string(table[r][c].key) + "-" + table[r][c].val;

                printCell(content, colWidth);
            }
            cout << endl;
        }
    }







        // #define PRINT_ROWS {1,3,5,7}

    void printKeysOnly() {
        int rows[] = BASIC;
        int rowCount = sizeof(rows)/sizeof(rows[0]);

        int maxWidth = 0;

        for (int i = 0; i < rowCount; i++) {
            int r = rows[i];
            for (int c = 0; c < 13; c++) {
                string content;
                if (table[r][c].key[0] != '\0')
                    content = table[r][c].key;

                int w = displayWidth(content);
                if (w > maxWidth) maxWidth = w;
            }
        }

        const int colWidth = maxWidth + 3;

        for (int i = 0; i < rowCount; i++) {
            int r = rows[i];
            for (int c = 0; c < 13; c++) {
                string content;
                if (table[r][c].key[0] != '\0')
                    content = table[r][c].key;

                printCell(content, colWidth);
            }
            cout << endl;
        }
    }






    void printValuesOnly() {
        int rows[] = BASIC;
        int rowCount = sizeof(rows)/sizeof(rows[0]);

        int maxWidth = 0;

        for (int i = 0; i < rowCount; i++) {
            int r = rows[i];
            for (int c = 0; c < 13; c++) {
                string content;
                if (table[r][c].key[0] != '\0')
                    content = table[r][c].val;

                int w = displayWidth(content);
                if (w > maxWidth) maxWidth = w;
            }
        }

        const int colWidth = maxWidth + 3;

        for (int i = 0; i < rowCount; i++) {
            int r = rows[i];
            for (int c = 0; c < 13; c++) {
                string content;
                if (table[r][c].key[0] != '\0')
                    content = table[r][c].val;

                printCell(content, colWidth);
            }
            cout << endl;
        }
    }


    string encodeString(const string& input)
    {
        string out = input;

        int rows[] = BASIC;
        int rowCount = sizeof(rows)/sizeof(rows[0]);

        for (int i = 0; i < rowCount; i++)
        {
            int r = rows[i];

            for (int c = 0; c < 13; c++)
            {
                if (table[r][c].key[0] == '\0') continue;

                string k = table[r][c].key;
                string v = table[r][c].val;

                size_t pos = 0;
                while ((pos = out.find(k, pos)) != string::npos)
                {
                    out.replace(pos, k.length(), v);
                    pos += v.length();
                }
            }
        }

        return out;
    }

    string decodeString(const string& input)
    {
        string out = input;

        int rows[] = BASIC;
        int rowCount = sizeof(rows)/sizeof(rows[0]);

        for (int i = 0; i < rowCount; i++)
        {
            int r = rows[i];

            for (int c = 0; c < 13; c++)
            {
                if (table[r][c].key[0] == '\0') continue;

                string k = table[r][c].key;
                string v = table[r][c].val;

                size_t pos = 0;
                while ((pos = out.find(v, pos)) != string::npos)
                {
                    out.replace(pos, v.length(), k);
                    pos += k.length();
                }
            }
        }

        return out;
    }


    void processFile(const string& filename, bool encode)
    {
        ifstream in(filename);
        string line;

        while (getline(in, line))
        {
            if (encode)
                cout << encodeString(line) << endl;
            else
                cout << decodeString(line) << endl;
        }
    }

};

int main() {
    Tamil t;

    // t.printTable();
    // t.printSelectedRows();
    // t.printKeysOnly();
    // t.printValuesOnly();

    t.printSelectedRows_S();


    cout << t.encodeString("a aa A") << endl;
    cout << t.decodeString("சபரி") << endl;

    // file processing
    // t.processFile("input.txt", true);   // encode
    // t.processFile("input.txt", false);  // decode

    return 0;
}