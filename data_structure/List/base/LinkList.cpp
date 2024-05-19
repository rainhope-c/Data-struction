//单链表LinkNode
//链表是在数据域之外增加指针域，指向下一个结点或者上一个结点的指针
//有点是插入元素或者删除元素更快，但是多了指针域需要更多的内存空间

template <typename T>
struct LinkNode  //单链表结点类型
{
    T data;  //存放数据元素
    LinkNode<T>* next;  //下一个结点的指针

    LinkNode():next(NULL);  //构造函数
    LinkNoded(T d):data(d),new(NULL);  //重载构造函数
};
template <typename T>
class LinkList
{
public:
    LinkNode<T>* head;  //单链表头结点


    LinkList()  //构造函数
    {
        head=new LinkNode<T>();
    }
    ~LinkList()  //析构函数
    {
        LinkNode<T>* pre,*p;
        pre=head;  p=pre->next;  //一个前驱结点一个后继结点
        while(p!=NULL)  //用p遍历结点并释放其前驱结点
        {
            delete pre;  //释放pre并且p同步后移
            pre=p; p=p->next;
        }
        delete pre;  //释放尾结点
    }

    //寻找序号为i的结点(不存储数据的头结点的序号为-1)，这个函数是链表核心功能的前提
    LinkNode<T>* geti(int i)  //返回序号为i的结点
    {
        if(i<-1)    return NULL;  //i<-1时返回NULL
        LinkNode<T>* p=hhead;  //首先p指向头结点
        int j=-1;  //j设置为-1(因为是把头结点看做序号为-1)
        while(j<i && p!=NULL)  //指针p移动i+1的结点
        {
            j++;
            p=p->next;
        }
        return p;  //找到后返回p
    }



    //将元素e添加到线性表的末尾
    void Add(T e)  
    {
        LinkNode<T>* s=new LinkNode<T>(e);  //新建结点s
        LinkList<T>* p=head;
        while(p->next!=NULL)  //查找尾结点p
            p=p->next;
        p->next=s;
    }
    //求线性表的长度
    int Getlength()
    {
        LinkNode<T>* p=head;
        int cnt=0;
        while(p->next!=NULL)
        {
            cnt++;
            p=p->next;
        }
        return cnt;
    }
    //求线性表中序号为i的元素GetElem
    bool GetElem(int i,T& e)
    {
        if(i<0) return false;
        LinkNode<T>* p=geti(i);  //查找序号i的结点
        if(p!=NULL)
        {
            e=p->data;
            return true;
        }
        else    return false;
    }
    //设置线性表中序号为i的多元素SetElem
    bool SetElem(int i,T e)
    {
        if(i<0) return false;
        LinkNode<T>* p=geti(i);  //查找序号i的结点
        if(p!=NULL)
        {
            p->data=e;
            return true;
        }
        else    return false;        
    }
    //求线性表中第一个值为e的元素的逻辑符号
    int GetNo(T e)
    {
        int j=0;  //置j为0.p指向首结点
        LinkNode<T>* p=head->next;
        while(p!=NULL && p->head->data!=e)
        {
            j++;
            p=p->next;
        }
        if(p==NULL) return -1;  //未找到时返回-1
        else    return j;  //找到后返回其序号
    }
    //在序号i的位置插入值为e的结点
    bool Insert(int i,T e)  
    {
        if(i<0)   return false;
        LinkNode<T>* s=new LinkNode<T>(e);  //建立新结点s
        LinkNode<T>* s=geti(i-1);  //查找序号为i-1的结点
        if(p!=NULL)
        {
            s->next=p->data;
            p->next=s;
            return true;
        }
        else    return false;
    }
    //删除第i个结点
    bool Delete(int i)
    {
        if(i<0)     return false;
        LinkNode<T>* p=geti(i-1);  //查找序号为i-1的结点
        if(p!=NULL)
        {
            LinkNode<T>* q=p->next;  //q指向需要被删除的结点
            if(q!=NULL)
            {
                p->next=q->next;
                delete q;
                return true;
            }
            else   
                return false;
        }
        else
            return false;
    }
    void DispList()
    {
        LinkNode<T>* p;
        p=head->next;
        while(p!=NULL)
        {
            cout<<p->data<<" ";
            p=p->next;
        }
        cout <<endl;
    }
    //头插法建立链表
    void CreateListF(T a[],int n)  //利用数组T和数组的元素n头插法建表
    {
        for(int i=0;i<n;i++)
        {
            LinkNode<T>* s=new LinkNode<T>(a[i]);  //遍历用数组的各个元素建立结点
            s->next=head->next;  //将结点s插到head结点后
            head->next=s;
        }
    }  //注意头插法建立的单链表的数据结点的次序与a数组中的次序相反
    //尾插法建表
    void CreateListR(T a[],int n)
    {
        LinkNode<T>* s,* r;
        r=head;  //r始终指向尾结点，开始时指向头结点
        for(int i=0;i<n;i++)
        {
            s=new LinkList<T>(a[i]);  //建立数据结点s
            r->next=s;  //把结点s插到结点r之后
            r=s;  //结点s变成新的尾结点
        } 
        r->next=NULL;  //将尾结点的next域设置为NULL
    }











};


