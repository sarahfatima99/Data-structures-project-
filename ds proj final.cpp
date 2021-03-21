#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<map>
#include<fstream>
using namespace std;
class TrieNode
{
	public:
		
		map<char,TrieNode*> children;
		int Weightage;
		
		TrieNode()
		{
		
			Weightage = false;
		}
};
class Tries{
	
	public:
	
		TrieNode *root ;
		float nuetral,negative,positive,prev,next;
		
		Tries(){
			
			nuetral=0;
			negative=-1;
			positive=0;
			prev=5;
			next=5;
			root = NULL ;
			root=new TrieNode();
		
		}
		
		void insert(TrieNode *temp,string word , int hh)
		{
			TrieNode *current = temp;
			for(int i=0;i<word.size();i++)
			{
				char ch=word[i];
				TrieNode *node=current->children[ch];
				if(!node)
				{
					node=new TrieNode();
					current->children[word[i]]=node;
				}
				current = node;
				//current->prefixes++;
			}
			current->Weightage=hh;
			//cout<<current->Weightage;
		}

		void search(TrieNode *temp,string word)
		{// cout<<word;
			TrieNode *current = temp;
			for(int i=0;i<word.size();i++)
			{
				char ch=word[i];
				TrieNode *node=current->children[ch];
				if(!node){
		
					return;
				}
				current=node;
			}
			if(current->Weightage!=2){
		
				prev=current->Weightage;
			}
			if(current->Weightage==2){
				nuetral=-1;
				next=prev;
			}
			//	return current->Weightage;
			if(current->Weightage==0){
				if(nuetral==-1){
		
				if(next!=5){
			
					if(next==1)
						negative++;
						if(next==0)
							positive++;
					nuetral=0;
		
				}
				else {
					positive++;
					nuetral=0;
				}	
				}
				else
					negative++;

			}
			if( current->Weightage==1){
				if(nuetral==-1){
					if(next!=5){
					
						if(next==1)
							negative++;
						if(next==0)
							positive++;
						nuetral=0;
					}
					else{
						negative++;
						nuetral=0;
					}
				}
				else
					positive++;
		
			}
			return;
		}
	
		int binarySearch(string arr[], int p, int r, string num) { 
   		
		   	if (p <= r)
			{ 
      			int mid = (p + r)/2; 
      			if (arr[mid] == num)   
         			return mid ; 
     			else if (arr[mid] > num)  
        			return binarySearch(arr, p, mid-1, num);            
    			else if (arr[mid] < num)
         			return binarySearch(arr, mid+1, r, num); 
   			} 
  			return -1; 
		}
		void removestopwords(char *str, int len)
		{
			string stopword[88] ={"a","about","above","after","again","against","all","am","an","and","any","are","as","at","be","because","before","being","between","both","by""for","did","do","does","doing","down","during","each","few","from","further","had","has","have","having","her","here","how","i","if","in","into","is","it","its","me","more","most","movie","my","of","off","once","or","other","our","out","over","overly","so","some","that","the","their","them","then","there","these","they","this","those","through","to","under","until","up","was","we","were","what","when","where","which","while","who","why","with","yet"};
			int flag=0;
			int w=0;
			string s,h;

			int n=sizeof(stopword)/sizeof(stopword[0]);
			char word[100], twoD[50][30],cleaned[50][30];
			int i = 0, j = 0, k = 0, len1 = 0, len2 = 0, m=0,l=0;
 
			// TOEKNIZATION
			for (i = 0; i<len; i++)
			{
				if (str[i] == ' ')
				{
					twoD[k][j] = '\0';
					k ++;
					j = 0;
				}
				else
				{
					if(str[i]!='.' )
					if(str[i]!='!')
					if(str[i]!=','){
			
						twoD[k][j] = str[i];
						j ++;
					}
					else break;
			
				}
			}
 
			twoD[k][j] = '\0';
 
			j = 0;
	   		for (i=0; i<=k+1; i++)
	      
	        { 
				s=twoD[i];
        		int x=binarySearch(stopword,0,n-1,s);
                if (x==-1)
                {
				  for(int n=0;n<s.size();n++){
				  	cleaned[l][m]=s[n];
				  	m++;
				  }
				  cleaned[l][m]='\0';
				  l++;
                }
                
				m=0;	

        	}
      		l--;
       		
			for(int u=0;u<l;u++)
    		{
	   			// cout<<cleaned[u];
	 		  this->search(this->root,cleaned[u]);
   			}
		}
		void creatpolarities(TrieNode *temp){
		
			string word;
			fstream f;
			char str[300];
			int i;
			f.open("polarities.txt",ios::in);
			while (f){
				f>>word;
				f>>i;
				this->insert(temp,word,i);

			}	
			string s;
			int a;
			f.close();
			f.open("movierevinputs.txt",ios::in);
			while(f){
	
	   			getline(f,s,'\n');

				for(int i=0; i<s.size();i++)
				{
					str[a]=s[i];
					a++;
				}
				s = '\0';
				if(f){

					str[a]=' ';
					a++;
				}


			}


			this->removestopwords(str,a);
			if(negative==-1){
				negative=0;	
			}
			float total=negative+positive;
			float neg=(negative/total)*100;
			float pos=(positive/total)*100;

			cout<<endl<<"you review is "<<neg<<"% negavtive and "<<pos<<"%"<<" positive";
		
			f.close();
		}
};

int main()
{
	Tries *obj=new Tries();
	obj->creatpolarities(obj->root);
	return 0;
}
