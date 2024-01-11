#include <bits/stdc++.h>
using namespace std;


struct Record
{
    int id;
    string user;
};

class recordManager
{
private:
    vector<Record> records;

public:
    void addRec(int id, const string& user)
    {
        Record newRecord {id, user};
        records.push_back(newRecord);
    }
    
    void delRec(int id)
    {
        records.erase(remove_if(records.begin(), records.end(), [id](const Record& record)
        {
            return record.id == id;
        }), records.end());
    }
    
    void editRec(int id, const string& changeUser)
    {
        for(auto& rec : records)
        {
            if(rec.id == id)
            {
                rec.user = changeUser;
                break;
            }
        }
    }
    
    void sortRec()
    {
        sort(records.begin(), records.end(), [](const Record& a, const Record& b) {
            return a.id < b.id;
        });
    }
    
    void dispRec()
    {
        for(const auto& record : records)
        {
            cout << "ID = " << record.id << ", User = " << record.user << endl;
        }
    }
};


int main() 
{
    recordManager recs;
    
    recs.addRec(1, "Pratyush");
    recs.addRec(4, "John");
    recs.addRec(2, "Jennifer");
    recs.addRec(3, "Alex");
    recs.addRec(5, "David");
    
    cout << "Unsorted Records: " << endl;
    recs.dispRec();
    
    cout << endl;
    
    recs.sortRec();
    cout << "Sorted Records: " << endl;
    recs.dispRec();
    
    cout << endl;
    
    recs.delRec(5);
    cout << "After Deletion of 5: " << endl;
    recs.dispRec();
    
    cout << endl;
    
    string data = "Ronaldo";
    recs.editRec(4, data);
    cout << "After editing record of John with ID 4 to Ronaldo" << endl;
    recs.dispRec();
    
    return 0;
}
