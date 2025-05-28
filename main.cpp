#include <iostream>
using namespace std;

struct Node
{
    char nama_ruangan[50];
    char nama_fasilitas[50];
    int jumlah;
    Node *prev;
    Node *next;
};

void sisipbelakang(Node *&head, const char *ruangan, const char *fasilitas, int jumlah);
Node *lastnode(Node *head);
void swap(Node *a, Node *b);
void quicksort(Node *low, Node *high);
Node *carinode(Node *head, const char *ruangan, const char *fasilitas);
void hapusdaritengah(Node *&head, const char *ruangan, const char *fasilitas);
void editnode(Node *head, const char *ruangan, const char *fasilitas);
void printdaridepan(Node *head);
void freelist(Node *&head);
char *custom_strncpy(char *dest, const char *src, size_t n);
int custom_strcmp(const char *s1, const char *s2);
string padRight(const string &str, int width);
void printperruang(Node *head, const char *ruanganCari);

bool cekfile(const char *namafile)
{
    FILE *file = fopen(namafile, "rb");
    if (file)
    {
        fclose(file);
        return true;
    }
    return false;
}

void simpan(Node *head, const char *namafile)
{
    FILE *file = fopen(namafile, "wb");
    if (!file)
    {
        perror("Error file tidak bisa dibuka");
        return;
    }
    while (head)
    {
        fwrite(head->nama_ruangan, sizeof(char), 50, file);
        fwrite(head->nama_fasilitas, sizeof(char), 50, file);
        fwrite(&head->jumlah, sizeof(int), 1, file);
        head = head->next;
    }
    fclose(file);
}

Node *load(const char *namafile)
{
    FILE *file = fopen(namafile, "rb");
    if (!file)
    {
        return nullptr;
    }

    Node *head = nullptr;
    char ruangan[50], fasilitas[50];
    int jumlah;
    while (fread(ruangan, sizeof(char), 50, file) &&
           fread(fasilitas, sizeof(char), 50, file) &&
           fread(&jumlah, sizeof(int), 1, file))
    {
        sisipbelakang(head, ruangan, fasilitas, jumlah);
    }
    fclose(file);
    return head;
}

void sisipbelakang(Node *&head, const char *ruangan, const char *fasilitas, int jumlah)
{
    if (carinode(head, ruangan, fasilitas))
    {
        cout << "catatan fasilitas tidak boleh sama dalam satu ruangan.\n";
        return;
    }

    Node *newNode = new Node;
    custom_strncpy(newNode->nama_ruangan, ruangan, 50);
    custom_strncpy(newNode->nama_fasilitas, fasilitas, 50);
    newNode->jumlah = jumlah;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    if (!head)
    {
        head = newNode;
    }
    else
    {
        Node *temp = head;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }

    quicksort(head, lastnode(head)); // Auto-sort after sisipbelakang
}

Node *carinode(Node *head, const char *ruangan, const char *fasilitas)
{
    while (head)
    {
        if (custom_strcmp(head->nama_ruangan, ruangan) == 0 && custom_strcmp(head->nama_fasilitas, fasilitas) == 0)
            return head;
        head = head->next;
    }
    return nullptr;
}

void hapusdaritengah(Node *&head, const char *ruangan, const char *fasilitas)
{
    Node *node = carinode(head, ruangan, fasilitas);
    if (!node)
    {
        cout << "fasilitas tidak ditemukan.\n";
        return;
    }
    if (node->prev)
    {
        node->prev->next = node->next;
    }
    else
    {
        head = node->next;
    }
    if (node->next)
    {
        node->next->prev = node->prev;
    }
    delete node;
    cout << "fasilitas dihapus.\n";
}

void editnode(Node *head, const char *ruangan, const char *fasilitas)
{
    Node *node = carinode(head, ruangan, fasilitas);
    if (!node)
    {
        cout << "fasilitas tidak ditemukan.\n";
        return;
    }
    cout << "Masukkan nama fasilitas baru: ";
    // cin.ignore();
    cin.getline(node->nama_fasilitas, 50);
    cout << "Masukkan jumlah baru: ";
    cin >> node->jumlah;
    cout << "fasilitas diperbarui.\n";
}

void printdaridepan(Node *head)
{
    const int colWidth = 26;

    cout << padRight("Fasilitas", colWidth)
         << padRight("Jumlah", colWidth)
         << padRight("Ruangan", colWidth) << endl;

    cout << string(colWidth * 3, '-') << endl;

    while (head)
    {
        cout << padRight(head->nama_fasilitas, colWidth);
        // to_string kalau error itu cuman false alarm
        cout << padRight(to_string(head->jumlah), colWidth);
        cout << padRight(head->nama_ruangan, colWidth) << endl;

        head = head->next;
    }
}

void printperruang(Node *head, const char *ruanganCari)
{
    const int colWidth = 26;
    bool ditemukan = false;

    cout << "Fasilitas di ruangan \"" << ruanganCari << "\":" << endl;
    cout << padRight("Fasilitas", colWidth)
         << padRight("Jumlah", colWidth)
         << padRight("Ruangan", colWidth) << endl;
    cout << string(colWidth * 3, '-') << endl;

    while (head)
    {
        if (custom_strcmp(head->nama_ruangan, ruanganCari) == 0)
        {
            ditemukan = true;
            cout << padRight(head->nama_fasilitas, colWidth)
                 << padRight(to_string(head->jumlah), colWidth)
                 << padRight(head->nama_ruangan, colWidth) << endl;
        }
        head = head->next;
    }

    if (!ditemukan)
    {
        cout << "Fasilitas kosong di ruangan ini.\n";
    }
}

void freelist(Node *&head)
{
    while (head)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
}

void swap(Node *a, Node *b)
{
    char temp_ruangan[50], temp_fasilitas[50];
    int temp_jumlah = a->jumlah;
    custom_strncpy(temp_ruangan, a->nama_ruangan, 50);
    custom_strncpy(temp_fasilitas, a->nama_fasilitas, 50);

    custom_strncpy(a->nama_ruangan, b->nama_ruangan, 50);
    custom_strncpy(a->nama_fasilitas, b->nama_fasilitas, 50);
    a->jumlah = b->jumlah;

    custom_strncpy(b->nama_ruangan, temp_ruangan, 50);
    custom_strncpy(b->nama_fasilitas, temp_fasilitas, 50);
    b->jumlah = temp_jumlah;
}

Node *lastnode(Node *head)
{
    while (head && head->next)
    {
        head = head->next;
    }
    return head;
}

void quicksort(Node *low, Node *high)
{
    if (high && low != high && low != high->next)
    {
        char pivot[50];
        custom_strncpy(pivot, high->nama_ruangan, 50);
        Node *i = low->prev;
        for (Node *j = low; j != high; j = j->next)
        {
            if (custom_strcmp(j->nama_ruangan, pivot) <= 0)
            {
                i = (i == nullptr) ? low : i->next;
                swap(i, j);
            }
        }
        i = (i == nullptr) ? low : i->next;
        swap(i, high);
        quicksort(low, i->prev);
        quicksort(i->next, high);
    }
}

// substitusi biar nggak harus pake cstring
char *custom_strncpy(char *dest, const char *src, size_t n)
{
    size_t i = 0;
    while (i < n && src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    while (i < n)
    {
        dest[i] = '\0';
        i++;
    }
    return dest;
}

// substitusi biar nggak harus pake cstring
int custom_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

string padRight(const string &str, int width)
{
    string result = str;
    while (result.length() < width)
    {
        result += ' ';
    }
    return result;
}

int main()
{
    const char *namafile = "inventaris.bin";
    Node *head = nullptr;

    // Load from file if exists
    if (cekfile(namafile))
    {
        head = load(namafile);
        cout << "Memuat data dari file\n";
    }
    else
    {
        cout << "File tidak ditemukan, membuat list baru\n";
    }

    int pilihan, jumlah;
    string nama, ruangan;

    do
    {
        cout << "\n=== Menu Inventaris Gedung Pattimura ===\n";
        cout << "1. Input Fasilitas \n";
        cout << "2. Hapus Fasilitas \n";
        cout << "3. Edit Fasilitas \n";
        cout << "4. Tampilkan Seluruh Fasilitas\n";
        cout << "5. Tampilkan Fasilitas di Satu Ruangan\n";
        cout << "6. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan)
        {
        case 1:
        {
            char ruangan[50], fasilitas[50];
            int jumlah;
            // cin.ignore();
            cout << "Masukkan nama ruangan : ";
            cin.getline(ruangan, 50);
            cout << "Masukkan nama fasilitas: ";
            cin.getline(fasilitas, 50);
            cout << "Masukkan Jumlah : ";
            cin >> jumlah;
            sisipbelakang(head, ruangan, fasilitas, jumlah);
            break;
        }
        case 2:
        {
            char ruangan[50], fasilitas[50];
            // cin.ignore();
            cout << "Masukkan nama ruangan: ";
            cin.getline(ruangan, 50);
            cout << "Masukkan fasilitas yang ingin dihapus: ";
            cin.getline(fasilitas, 50);
            hapusdaritengah(head, ruangan, fasilitas);
            break;
        }
        case 3:
            char ruangan[50], fasilitas[50];
            // cin.ignore();
            cout << "Masukkan nama ruangan: ";
            cin.getline(ruangan, 50);
            cout << "Masukkan nama fasilitas: ";
            cin.getline(fasilitas, 50);
            editnode(head, ruangan, fasilitas);
            break;
        case 4:
            if (!head)
            {
                cout << endl;
                cout << "list kosong" << endl;
            }
            else
            {
                cout << endl;
                printdaridepan(head);
            }
            break;
        case 5:
        {
            if (!head)
            {
                cout << endl;
                cout << "list kosong" << endl;
            }
            else
            {
                char ruangan[50];
                // cin.ignore();
                cout << "Masukkan nama ruangan yang ingin ditampilkan: ";
                cin.getline(ruangan, 50);
                cout << endl;
                printperruang(head, ruangan);
            }
            break;
        }
        case 6:
            cout << "Terima kasih.\n";
            break;
        default:
            cout << "Pilihan tidak valid.\n";
        }

        simpan(head, namafile);
    } while (pilihan != 6);

    freelist(head);
    return 0;
}