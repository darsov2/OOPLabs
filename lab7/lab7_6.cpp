//
// Created by David Arsov on 2.5.2022.
//

#include <bits/stdc++.h>

using namespace std;

class Task
{
protected:
    char ID[5];

public:
    Task(char *i = "")
    {
        strncpy(ID, i, 5);
    }

    ~Task()
    {

    }

    virtual int getOrder() = 0;

    virtual void print() = 0;

    char *getID()
    {
        return ID;
    }
};

class TimedTask : public Task
{
private:
    int time;

public:
    TimedTask(char *i = "", int t = 0) : Task(i)
    {
        time = t;
    }

    int getOrder()
    {
        return time;
    }

    void print()
    {
        cout << "TT->" << ID << ":" << getOrder() << endl;
    }
};

class PriorityTask : public Task
{
private:
    int priority;

public:
    PriorityTask(char *i = "", int p = 0) : Task(i)
    {
        priority = p;
    }

    int getOrder()
    {
        return priority;
    }

    void print()
    {
        cout << "PT->" << ID << ":" << getOrder() << endl;
    }
};

bool operator==(Task *t1, Task &t2)
{
    return (!strcmp(t1->getID(), t2.getID()) && t1->getOrder() == t2.getOrder());
}

void scheduleTimedTasks(Task **tasks, int n, int t)
{
    Task **temp = new Task*[n];
    int j = 0;
    for(int i = 0; i < n; i++)
    {
        TimedTask *tt = dynamic_cast<TimedTask*>(tasks[i]);
        if(tasks[i]->getOrder() < t && tt != 0)
        {
            temp[j] = tasks[i];
            j++;
        }
    }

    for(int i = 0; i < j; i++)
    {
        for(int k = i + 1; k < j; k++)
        {
            if(temp[i]->getOrder() > temp[k]->getOrder())
            {
                swap(temp[i], temp[k]);
            }
        }
    }

    for(int i = 0; i < j; i++)
    {
        temp[i]->print();
    }
}

void schedulePriorityTasks(Task **tasks, int n, int t)
{
    Task **temp = new Task*[n];
    int j = 0;
    for(int i = 0; i < n; i++)
    {
        PriorityTask *pt = dynamic_cast<PriorityTask*>(tasks[i]);
        if(tasks[i]->getOrder() < t && pt != 0)
        {
            temp[j] = tasks[i];
            j++;
        }
    }

    for(int i = 0; i < j; i++)
    {
        for(int k = i + 1; k < j; k++)
        {
            if(temp[i]->getOrder() > temp[k]->getOrder())
            {
                swap(temp[i], temp[k]);
            }
        }
    }

    for(int i = 0; i < j; i++)
    {
        temp[i]->print();
    }
}

int main () {
    int testCase;
    int n;
    cin>>testCase;

    if (testCase==0){
        cin>>n;
        Task ** tasks;
        tasks = new Task * [n];
        for (int i=0;i<n;i++){
            char id [5];
            int timeOrPriority;
            int type; //0 za timed, 1 za priority
            cin >> type >>id >> timeOrPriority;
            if (type==0)
                tasks[i] = new TimedTask(id,timeOrPriority);
            else
                tasks[i] = new PriorityTask(id,timeOrPriority);
            //tasks[i]->print();
        }

        cout<<"SCHEDULING PRIORITY TASKS WITH PRIORITY DEGREE LESS THAN 10"<<endl;
        schedulePriorityTasks(tasks,n,10);

    }
    else if (testCase==1) {
        cin>>n;
        Task ** tasks;
        tasks = new Task * [n];
        for (int i=0;i<n;i++){
            char id [5];
            int timeOrPriority;
            int type; //0 za timed, 1 za priority
            cin >> type >>id >> timeOrPriority;
            if (type==0)
                tasks[i] = new TimedTask(id,timeOrPriority);
            else
                tasks[i] = new PriorityTask(id,timeOrPriority);
            //tasks[i]->print();
        }


        cout<<"SCHEDULING TIMED TASKS WITH EXECUTION TIME LESS THAN 50"<<endl;
        scheduleTimedTasks(tasks,n,50);
    }
    else {
        TimedTask * tt1 = new TimedTask("11",10);
        TimedTask * tt2 = new TimedTask("11",11);
        TimedTask * tt3 = new TimedTask("11",11);
        PriorityTask * pp1 = new PriorityTask("aa",10);
        PriorityTask * pp2 = new PriorityTask("11",10);

        cout << (tt1==(*tt2))<<endl;
        cout << (tt2==(*tt3))<<endl;
        cout << (pp1==(*pp2))<<endl;
        cout << (pp2==(*tt1))<<endl;
    }

    return 0;
}