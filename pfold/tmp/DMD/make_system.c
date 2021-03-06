#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "bcp.h"
#include "controls.h"
#include "movie.h"
#include "make_system.h"
#include "search.h"
#include "bonds.h"
#include "corr_func.h"
#include "cluster.h"
#include "rms.h"
#include "phipsi.h"

extern  FILE * text_path;
extern  int n,n1,nen,nen1;
extern  int nrt;
extern  double dticks;
static  double dblarg1=DBL1;
static  double dblarg2=DBL2;
extern  atom *a;
extern  CollisionData *coll;
extern  ReactionData *react;
extern  dimensions bound[3];
extern  crd o;
extern  double dim;
extern  char* isPerm;


static  atom * sam;
int nat;
extern  well_type ** ecoll;
extern  well_type ** icoll;
extern  well_type ** ncoll;/*for searching of neighbour collision*/
extern  well_type * collp;
extern  well_type * collq;
extern  well_type * collr;
static  line_number;
static  unsigned char **keywords; 
static int n_keywords;
static int *keyfound;
static unsigned char * endbuf;
static well_type ntot;
static int write_start;
static int write_finish;
static int write_n1;
static int write_stop;

int is_hb=0;
extern int is_en;

/*temperary: measure the lift time of hydrogenbonds*/
/**/
double** hb_dt;
double** hb_dt_prev;
int**  hb_n;


void set_write_param(int n0,int n1,int yes)
{
  write_start=n0;
  write_finish=n0+n1;
  write_n1=n1;
  write_stop=yes;
}

void init_coll( well_type j, well_type prev, well_type next, double mi,double mj ,double en,double diam,int react)
{ 
/*  printf("%d",j);*/
  double dd = diam*diam;
  double dm = 0;
  double edm = 0;
  double mu = 0;
  double dmu = 0;
  
  if(mi<m_max){
    if(mj<m_max){
      dm=1.0/((mi+mj)*dd);
      mu = (mi*mj)/(mi+mj);
      dmu = dd/mu;
      if(en!=dblarg1) edm=-2.0*en/(mi*mj*dm);
    }
    else{
      mu = mi;
      dmu = dd/mu;
      if(en!=dblarg1) edm=-2.0*en*dd/mi;
    }
  }
  else{
    if(mj<m_max){
      mu = mj;
      dmu = dd/mu;
      if(en!=dblarg1) edm=-2*en*dd/mj;
    }
  }
  
  coll[j].dd = dd;  
  coll[j].mu = mu;
  coll[j].dmu = dmu;
  coll[j].e = coll[j].eo = -en;
  /*printf("HI\n");*/
  coll[j].dm = dm;
  coll[j].edm = coll[j].edmo = edm;
  coll[j].prev=prev;
  coll[j].next=next;
  coll[j].react=react;
  /*printf(" well\n");*/
}

int allocReact(ReactionData * react1, int nrt1, ReactionData * react0, int nrt0)
{
  if(nrt0+nrt1==0)
    return 0;  
  if(!nrt0)
    {
      react=react1;
      return nrt1;
    }
  if(!nrt1)
    {
      react=react0;
      return nrt0;
    }
  if((nrt1>0)&&(nrt0>0))
    {
      int i,j,k,ntr;
      k=0;
      for(i=1;i<=nrt0;i++)
	{
	  for(j=1;j<=nrt1;j++)
	    {
	      if(react1[j].bond)
		{
		  if(((react0[i].new1==react1[j].new1)&&(react0[i].new2==react1[j].new2))||
		     ((react0[i].new1==react1[j].new2)&&(react0[i].new2==react1[j].new1)))
		    {
		      react0[i].old1=0;
		      k++;
		      break;
		    }
		}
	      if(((react0[i].old1==react1[j].old1)&&(react0[i].old2==react1[j].old2))||
		 ((react0[i].old1==react1[j].old2)&&(react0[i].old2==react1[j].old1)))
		{
		  react0[i].bond=-1;
		  break;
		}
	    }
	}
      nrt=nrt1+nrt0-k;
      react=(ReactionData *)malloc((nrt+1)*sizeof(ReactionData));
      if(!react){StopAlert (MEMORY_ALRT);return -1;}      
      for(i=1;i<=nrt1;i++)
	react[i]=react1[i];
      k=nrt1;
      for(i=1;i<=nrt0;i++)
	if(react0[i].old1>0)
	  {
	    k++;
	    react[k]=react0[i];
	  }
      free(react1);
      free(react0);
      for (i=1;i<=nrt;i++)
	printf("%d %d %d %d %d %lf %lf\n",react[i].old1,react[i].old2,
	       react[i].new1,react[i].new2,react[i].bond,react[i].dd,react[i].eo);
      return nrt;
    }
}

int write_key_coord(FILE * path)
{
   int nbyte;
   unsigned char s[512];
   int i,j,k; 
   int fErr=noErr;
   int free=get_free();
   double dlmin=bound[0].dl;
   double corr=get_corr();
   double mf=get_maxfree();
   moved_atom * a=(moved_atom *)get_atom();
   moveatoms();
   if(bound[1].dl<dlmin)dlmin=bound[1].dl;
   if(bound[2].dl<dlmin)dlmin=bound[2].dl;
   nbyte=sprintf(&s[0],
		 "//(simulation time %lf)\n//length of search table ( %ld current length)\n//corr=%le\n//ll=%ld\n",
		 get_time(),free,corr,get_ll());
   if(nbyte<=0) fErr=-1;    
   if(fErr==noErr)fErr=(fwrite(&s[0],1,nbyte,path)!=nbyte);
   if(fErr==noErr)
     {
       if(dim<3)     
	 nbyte=sprintf(&s[0],"%s\n%.7lf %.7lf\n%s\n%ld\n",
		       keywords[SYS_SIZE],bound[0].length,bound[1].length,
		       keywords[2],write_n1);
       else
	 nbyte=sprintf(&s[0],"%s\n%.7lf %.7lf %.7lf\n%s\n%ld\n",
		       keywords[1],bound[0].length,bound[1].length,bound[2].length,keywords[NUM_ATOMS],write_n1);
     }
   if(nbyte<=0) fErr=-1;    
   if(fErr==noErr)fErr=(fwrite(&s[0],1,nbyte,path)!=nbyte);
   if(fErr==noErr)
     nbyte=sprintf(&s[0],"%s\n//type,mass,ellastic radius,interaction radius\n",
		   keywords[TYPE_ATOMS]);
   if(nbyte<=0) fErr=-1;    
   if(fErr==noErr)fErr=(fwrite(&s[0],1,nbyte,path)!=nbyte);	 
   if(fErr==noErr) 
     for(k=1;k<=nat;k++)
       {
	 nbyte=sprintf(&s[0],"%ld %lf %lf %lf\n",k,sam[k].m,sam[k].s,sam[k].b);
	 if(nbyte<=0) fErr=-1;
	 if(fErr==noErr)fErr=(fwrite(&s[0],1,nbyte,path)!=nbyte);
	 if(fErr!=noErr)break;
       }


   

   if(fErr==noErr)
     nbyte=sprintf(&s[0],"%s\n//pair types, repulsive dist, interaction distance, energy\n"
		   ,keywords[NONEL_COL]);
   if(nbyte<=0) fErr=-1;    
   if(fErr==noErr)fErr=(fwrite(&s[0],1,nbyte,path)!=nbyte);	 
   if(fErr==noErr) 
     for(i=1;i<=nat;i++)
       for(j=1;j<=i;j++)
	 {
	   k=ecoll[i][j];
	   if(coll[k].next>-1)
	     {
	       double dd, en;
               int sbyte=0;
	       while(coll[k].next>-1)
		 k=coll[k].next;
	       dd=sqrt(coll[k].dd);
	       nbyte=sprintf(&s[0],"%d %d %lf \n",i,j,dd);
               sbyte+=nbyte-1; 
	       if(nbyte<=0) 
		 fErr=-1;
	       else
		 while(coll[k].prev>-1)
		   {
		     k=coll[k].prev;
		     dd=sqrt(coll[k].dd);
		     en=-coll[k].eo;
		     nbyte=sprintf(&s[sbyte],"%lf %lf \n",dd,en);
		     sbyte+=nbyte-1; 
		     if(nbyte<=0){fErr=-1;goto hell;}
		   } 
	       sbyte++;
	       if(fErr==noErr)fErr=(fwrite(&s[0],1,sbyte,path)!=sbyte);
	       if(fErr!=noErr)goto hell;
	     }
	 }

  if(fErr==noErr)
  nbyte=sprintf(&s[0],"%s\n//pair types, repulsive dist\n",keywords[EL_COL]);
  if(nbyte<=0) fErr=-1;    
  if(fErr==noErr)fErr=(fwrite(&s[0],1,nbyte,path)!=nbyte);	 
  if(fErr==noErr) 

   if(fErr==noErr) 
     for(i=1;i<=nat;i++)
       for(j=1;j<=i;j++)
	 {
	   k=ecoll[i][j];
	   if(coll[k].next<0)
	     {
	       double dd;
	       dd=sqrt(coll[k].dd);
	       nbyte=sprintf(&s[0],"%d %d %lf\n",i,j,dd);
	       if(nbyte<=0) 
		 {fErr=-1;goto hell;}
	       if(fErr==noErr)fErr=(fwrite(&s[0],1,nbyte,path)!=nbyte);
	       if(fErr!=noErr)goto hell;
	     }
	 }

   nbyte=sprintf(&s[0],"%s\n//pair types, repulsive dist, attractive distance\n",
		 keywords[LINK_PAIRS]);
   if(nbyte<=0) fErr=-1;    
   if(fErr==noErr)fErr=(fwrite(&s[0],1,nbyte,path)!=nbyte);	 	   	 

   if(fErr==noErr) 
     for(i=1;i<=nat;i++)
       for(j=1;j<=i;j++)
	 {
	   k=icoll[i][j];
	   if(k>-1)
	     {
	       double dd, en;
               int sbyte=0;
	       while(coll[k].next>-1)
		 k=coll[k].next;
	       dd=sqrt(coll[k].dd);
	       nbyte=sprintf(&s[0],"%d %d %lf \n",i,j,dd);
               sbyte+=nbyte-1; 
	       if(nbyte<=0) 
		 fErr=-1;
	       else
		 while(coll[k].prev>-1)
		   {
		     k=coll[k].prev;
		     dd=sqrt(coll[k].dd);
		     en=-coll[k].eo;
                     if(en!=dblarg1)
		       nbyte=sprintf(&s[sbyte],"%lf %lf \n",dd,en);
		     else
		       nbyte=sprintf(&s[sbyte],"%lf \n",dd);
		     sbyte+=nbyte-1; 
		     if(nbyte<=0){fErr=-1;goto hell;}
		   } 
	       sbyte++;
	       if(fErr==noErr)fErr=(fwrite(&s[0],1,sbyte,path)!=sbyte);
	       if(fErr!=noErr)goto hell;
	     }
	 }
   
   if(fErr==noErr)
     nbyte=sprintf(&s[0],"%s\n//old1,old2,new1,new2,bond,radius energy\n",keywords[REACT]);
   if(nbyte<=0) fErr=-1;    
   if(fErr==noErr)fErr=(fwrite(&s[0],1,nbyte,path)!=nbyte);	 
   if(fErr==noErr) 
     for(k=1;k<=nrt;k++)
       {
	 nbyte=sprintf(&s[0],"%d %d %d %d %d %lf %lf\n",
		       react[k].old1,
		       react[k].old2,
		       react[k].new1,
		       react[k].new2,
		       react[k].bond,
		       sqrt(react[k].dd),
		       react[k].eo);
	 if(nbyte<=0) fErr=-1;
	 if(fErr==noErr)fErr=(fwrite(&s[0],1,nbyte,path)!=nbyte);
	 if(fErr!=noErr)break;
       }

  if(fErr==noErr)
  nbyte=sprintf(&s[0],"%s\n//number, type, x, y, z, Vx, Vy, Vz\n",keywords[LIST_ATOMS]);
  if(nbyte<=0) fErr=-1;    
  if(fErr==noErr)fErr=(fwrite(&s[0],1,nbyte,path)!=nbyte);	 	   
  if(fErr==noErr)
    if(write_stop)stop_atoms((moved_iatom *)(a+write_start),write_n1);
    else corr_vel(); 	 
  for(i=write_start;i<write_finish;i++)
  {
    double x=a[i].r.x;
    double y=a[i].r.y;
    double z=a[i].r.z;
    if(x<0)x+=bound[0].length;
    if(y<0)y+=bound[1].length;
    if(z<0)z+=bound[2].length;
    if(x>bound[0].length)x-=bound[0].length;
    if(y>bound[1].length)y-=bound[1].length;
    if(z>bound[2].length)z-=bound[2].length;
    nbyte=sprintf(&s[0],"%4ld %4d %18.13lf %18.13lf %18.13lf %18.13lf %18.13lf %18.13lf\n",
    i+1-write_start,a[i].c,x,y,z,
    a[i].u.x,a[i].u.y,a[i].u.z);
    if(nbyte<=0) fErr=-1;  
    if(fErr==noErr)fErr=(fwrite(&s[0],1,nbyte,path)!=nbyte);
    if(fErr!=noErr)break;
  }
   
   if(fErr==noErr)
    nbyte=sprintf(&s[0],"%s\n//number1,number2\n",keywords[LIST_BONDS]);
   if(nbyte<=0) fErr=-1;    
   if(fErr==noErr)fErr=(fwrite(&s[0],1,nbyte,path)!=nbyte);	 	   
   if(fErr==noErr) 	 
    for(i=0;i<n1;i++)
	{ 
	  int index=-1;
	  do
	    {
	      j=nextFriend(i,&index);
	      if(index==-1)break;
	      if((j>i)&&(i>=write_start)&&(j<write_finish))
		{
		  nbyte=sprintf(&s[0],"%4ld %4ld\n",
				i+1-write_start,j+1-write_start);
		  if(nbyte<=0) fErr=-1;  
		  if(fErr==noErr)fErr=(fwrite(&s[0],1,nbyte,path)!=nbyte);
		  if(fErr!=noErr)break;
		}
	    }while(index>-1);
	}
   
   if(isPerm){
     if(fErr==noErr)
       nbyte=sprintf(&s[0],"%s\n//number1,number2,origType1,origType2\n",keywords[LIST_PERM_BONDS]);
     if(nbyte<=0) fErr=-1;    
     if(fErr==noErr)fErr=(fwrite(&s[0],1,nbyte,path)!=nbyte);	 	   
     if(fErr==noErr) 	 
       for(i=0;i<n1;i++)
	 { 
	   int index=-1;
	   do
	     {
	       j=nextPermBonds(i,&index);
	       if(index==-1)break;
	       if(j>=0&&(j>i)&&(i>=write_start)&&(j<write_finish))
		 {
		   nbyte=sprintf(&s[0],"%4ld %4ld %4ld %4ld\n",
				 i+1-write_start,j+1-write_start,
				 a[i-write_start].origc,a[j-write_start].origc);
		   if(nbyte<=0) fErr=-1;  
		   if(fErr==noErr)fErr=(fwrite(&s[0],1,nbyte,path)!=nbyte);
		   if(fErr!=noErr)break;
		 }
	     }while(index>-1);
	 }
   }
   if(is_hb){
     if(fErr==noErr)
       nbyte=sprintf(&s[0],"%s\n//atome number, gid, hb association1, hb association2\n",keywords[HB_LIST]);
     if(nbyte<=0) fErr=-1;    
     if(fErr==noErr)fErr=(fwrite(&s[0],1,nbyte,path)!=nbyte);	 	   
     if(fErr==noErr) 	 
       for(i=0;i<n1;i++){
	 if(a[i].hb>0){
	   nbyte=sprintf(&s[0],"%4ld %4ld %4ld",i+1-write_start, a[i].gid, a[i].hb_a1+1-write_start);
	   if(a[i].hb==2)nbyte+=sprintf(&s[nbyte]," %4ld",a[i].hb_a2+1-write_start);
	   s[nbyte]='\n';nbyte++;
	   if(nbyte<=0) fErr=-1;  
	   if(fErr==noErr)fErr=(fwrite(&s[0],1,nbyte,path)!=nbyte);
	   if(fErr!=noErr)break;
	 }
	 else if(a[i].hb==0){
	   nbyte=sprintf(&s[0],"%4ld %4ld\n",i+1-write_start, a[i].gid);
	   if(nbyte<=0) fErr=-1;  
	   if(fErr==noErr)fErr=(fwrite(&s[0],1,nbyte,path)!=nbyte);
	   if(fErr!=noErr)break;
	 }
       }
   }
   if(is_en){
     if(fErr==noErr)
       nbyte=sprintf(&s[0],"%s\n//atome number, gid\n",keywords[GID_LIST]);
     if(nbyte<=0) fErr=-1;    
     if(fErr==noErr)fErr=(fwrite(&s[0],1,nbyte,path)!=nbyte);	 	   
     if(fErr==noErr)
       for(i=0; i<n1; i++)
	 if(a[i].rid>=0){
	   nbyte=sprintf(&s[0], "%6ld %6ld\n",i+1-write_start, a[i].rid);
	   if(nbyte<=0) fErr=-1;  
	   if(fErr==noErr)fErr=(fwrite(&s[0],1,nbyte,path)!=nbyte);
	   if(fErr!=noErr)break;
	 }
   }
 hell:
   if(fErr!=noErr)fclose(path);
   return fErr;
}


unsigned char * get_buffer(int * file_length) 
{   
  int fErr; 
  int file_size;
  unsigned char * buf;
  
  
  /* fErr=GetEOF(text_path,&file_size);*/
  fErr=fseek(text_path,0,SEEK_END);
  if(fErr==noErr)file_size=ftell(text_path);
  if(file_size<=0)fErr=-1;
  if(fErr==noErr)fErr=fseek(text_path,0,SEEK_SET);
   if(fErr!=noErr){fclose(text_path); return NULL;}
   buf=(unsigned char *)malloc(file_size+2);
   if(!buf){StopAlert (MEMORY_ALRT);fclose(text_path);return NULL;}
   buf[0]='\n';
   fErr=(fread(buf+1,1,file_size,text_path)!=file_size);
   if(fErr!=noErr){fclose(text_path);free(buf); return NULL;}
   endbuf=buf+file_size+1;
   file_length[0]=file_size;
   return buf;
   }

/* finds the first line that does not begin with '/' */

unsigned char * next_line1(unsigned char * s)
{ unsigned char * t=s;
 
  do{
  while ((*t)!='\n')
  {
  if ((*t)=='\0')*t=' ';
  else if((*t)==(unsigned char)'\377')return NULL;
  t++;
  }
  *t='\0';t++;line_number++;
  }while ((*t)=='/');
  return t; 
 }

 /* Finds the first non-spaces charachter after at least one '\n'
which is before '/'.
Fills all preceedings characters between '/' and '\n' with 
spaces and all preceeding '\n' with '\0' and all
preceeding '\0' and '/' with spaces */   

unsigned char * next_line(unsigned char * s)
{ 
  unsigned char * t=s;
  int first=1;
  int slash=0;
  do
    {
      while ((*t)!='\n')
	{
	  if(t==endbuf)return NULL;
	  if ((*t)=='\0')*t=' ';
	  
	  if (!slash)
	    {
	      if ((*t)=='/'){*t=' ';slash=1;}
	      else if(!isspace(*t))
		{if(!first) return t;}
	    }
	  else
	    *t=' ';
	  t++;
	}
      line_number++;
      *t='\0';
      first=0;
      slash=0;
      if(t==endbuf)return NULL;
      t++;
    }while (1);
}
int isparam(unsigned char * datfile)
{
return 0;
}
int iskeyword(unsigned char * datfile)
{
/* Keywords should go in a specific order.
important keys are:
SYS_SIZE
NUM_ATOMS
TYPE_ATOMS
LIST_ATOMS
If a keyword is found twice
it is a bug. 
Returns key_word number; 
returns -1 if error; 
returns 0 if not a keyword */
  size_t l;
  int i,j,k;
  unsigned char * t;
  for(i=1;i<=n_keywords;i++)
    {  
      l=strlen(keywords[i]);
      t=datfile+l;
      if(strncmp(keywords[i],datfile,l))continue;
      for(j=i;j<=n_keywords;j++)
	if(keyfound[j])return -1;
      keyfound[i]=1;
      k=i; 
      if(k>3)k=3;
      for(j=1;j<=k;j++)
	if(!keyfound[j])return -1;
      if((i>LIST_ATOMS)&&(!keyfound[LIST_ATOMS]))return -1;
      while (isspace(*t))
	{ 
	  if((*t)=='\0')return i;
	  t++;
	}
      if((*t)=='\0')return i;
      else return -1;
    }
  return 0;
}

  
unsigned char * next_word(unsigned char * s)
{ 
  unsigned char * t=s;
  while (isspace(*t))
  { 
    if((*t)=='\0')return NULL;
    t++;
  }
  while(!isspace(*t))
  {
   if ((*t)=='\0')return NULL;
   t++;
   }
  return t; 
  }

int is_word(unsigned char * s)
{ 
  unsigned char * t=s;
  while (isspace(*t))
  { 
    if((*t)=='\0')return 0;
    t++;
  }
  if((*t)=='\0')return 0;
    else return 1;

}

int dimensionality( int * is_x)
{ 
  int i,j,k=0;
  iatom * b=(iatom *)a;
  for(i=0;i<3;i++)
  {
  is_x[i]=0;
  for(j=0;j<n1;j++)
  if ((b[j].r[i])||(b[j].v[i])) {is_x[i]=1;break;}
  k+=is_x[i];
  }
  return k; 
}

int make_tables(int isfile)
{  
  int err;
  int is_x[3];
  if(!dimensionality(is_x))return 0;
  init_update_param(is_x);
  if(!allocsearch(n1)){StopAlert (MEMORY_ALRT);return -1;}
  err=init_tables();
  if(err!=1)return err;
  init_rms();
  init_clusters();
  init_corr_func();
  //init_misc();
  init_phipsi();
  return 1;
}

int init_keywords()
{ 
  int i;   
  keywords=(unsigned char **)malloc(20*sizeof(unsigned char *));
  if(!keywords) return 0;
  keyfound=(int *)malloc(20*sizeof(int));
  if(!keyfound) return 0;
  n_keywords=15; 
  keywords[SYS_SIZE]="A.SYSTEM SIZE";
  keywords[NUM_ATOMS]="B.NUMBER OF ATOMS";
  keywords[TYPE_ATOMS]="C.TYPES OF ATOMS";
  keywords[NONEL_COL]="D.NON-ELASTIC COLLISIONS";
  keywords[EL_COL]="E.ELASTIC COLLISIONS";
  keywords[LINK_PAIRS]="F.LINKED PAIRS";
  keywords[REACT]="G.REACTIONS";
  keywords[LIST_ATOMS]="H.LIST OF ATOMS";
  keywords[LIST_BONDS]="I.LIST OF BONDS";
  keywords[LIST_PERM_BONDS]="IJ.LIST OF PERMANENT BONDS";
  keywords[NUM_BONDS]="J.BOND TABLE LENGTH";
  keywords[LIST_PARAM]="K.LIST OF PARAMETERS";
  keywords[COL_TABLE]="COLLISION TABLE LENGTH";
  keywords[HB_LIST]="L.LIST OF HYDROGEN BONDING ASSOCIATIONS";
  keywords[GID_LIST]="M.LIST OF GID";
  for(i=0;i<=n_keywords;i++)
  keyfound[i]=0;
  return 1;
}

int startup(void)
{
  int isfile,err,i,j;
  double file_type;
  if(!init_keywords())return -4;
  dblarg1=DBL1;
  dblarg2=DBL2;
  isfile=readfile();
  if(isfile==TEXT)
    {   
      int file_length;
      unsigned char * buf=get_buffer(&file_length);
      unsigned char * datfile, *nextline= buf;
      if(!buf)return -4; 
      
      line_number=MOVIE-1;
      nextline=next_line(nextline);
      datfile=nextline;if(!(nextline=next_line(datfile)))return line_number;
      /*      What is window size */
      i=iskeyword(datfile);
      if(i>0)err=make_key_system(i,nextline,file_length);
      else
	return line_number;
      if(err!=1)return err;
      free(buf);
      init_parameters();
    }
  j=make_tables(isfile);
  return j;
}

int make_bonds(int numbond, double * bonds)
{
int i;
int actual_number=0;
int res;
int friend1, friend2;
for (i=0;i<numbond;i++)
  {
    friend1=*bonds;
    bonds++;
    friend2=*bonds;
    bonds++;
    res=setBond(friend1,friend2);
    if(res<0)
      {return -1;}
    if(res==1)
      {return -1;}
    actual_number+=res;
  }
return actual_number;   
}

int makePermBonds(int numbond, double * bonds)
{
  int i;
  int actual_number=0;
  int res;
  int friend1, friend2;
  for (i=0;i<numbond;i++)
    {
      friend1=*bonds;
      bonds++;
      friend2=*bonds;
      bonds++;
      //printf("%ld %ld\n", friend1, friend2);
      res=setPerm(friend1,friend2);
      if(res<0)
	{return -1;}
      actual_number+=res;
      bonds+=2;
    }
  return actual_number;   
}

void printwells(well_type **icoll, int nat)
{
  int i,j,next;
  CollisionData x;
  FILE *ff;
  char name[100];
  printf("well output?\n");
  scanf("%s",name);
  ff=fopen(name,"w");
  for(i=1;i<=nat;i++)
    for(j=1;j<=i;j++)
      {
	next=icoll[i][j];
	while(next>-1)
	  {
	    x=coll[next];
	    fprintf(ff,"%d %d %d %d %d %d %lf %le %le\n",i,j,next, (int)x.next,(int)x.prev,(int)x.react,x.dd,x.eo,x.etot);
	    next=x.next;
	  }
      }
  fprintf(ff,"%d %d\n",nen,nen1);
  fclose(ff);
}
int make_wells(
double *** coldata,int numwell,
double *** bonddata,int numbondwell,
double * bonds,int numbond,atom * a,int nAtom,atom * sam,int nat)
{

/* nen is number of wells with finite energy barrier */
/* values larger or equal than nen1 are wells with infinite energy*/
  int i,j,k,l,nat2,unstable;
  well_type num,next,prev;
  double en;
  ntot=numwell+numbondwell+nrt;
  for(i=1;i<=nat;i++)
    for(j=1;j<=i;j++)
      if(!coldata[i][j])ntot++;
  for(k=0;k<numbond;k++)
    {
      i=bonds[2*k];
      j=bonds[2*k+1];
      if(isPerm && isPermBonds(i,j)){
	i=a[i].origc;
	j=a[j].origc;
      }
      else{
	i=a[i].c;
	j=a[j].c;
      }
      if(j>i){l=i;i=j;j=l;}
      if(!bonddata[i][j])
	{
	  bonddata[i][j]=bonds+2*k;
	  ntot+=2;
	}
    }
/*  printf("%d\n",ntot);*/
  nat2=(nat+1)*(nat+1);

  if(is_en){/*used for neighbour collision: rmin q.hdc+p.hdc e_max*/
    ncoll=(well_type **)malloc((nat+1)*sizeof(well_type *));
    if(!ncoll){StopAlert (MEMORY_ALRT);return line_number;}
    ncoll[0]=(well_type *)malloc(nat2*sizeof(well_type));
    if(!ncoll[0]){StopAlert (MEMORY_ALRT);return line_number;}
    for(i=0;i<nat;i++)
      ncoll[i+1]=ncoll[i]+nat+1;
    for(i=0;i<nat2;i++)
      ncoll[0][i]=-1;
    ntot += (nat*(nat+1))/2;
  }

  coll=(CollisionData *)malloc(ntot*sizeof(CollisionData));
  if(!coll)return 0; 

  ecoll=(well_type **)malloc((nat+1)*sizeof(well_type *));
  if(!ecoll){StopAlert (MEMORY_ALRT);return line_number;}
  ecoll[0]=(well_type *)malloc(nat2*sizeof(well_type));
  if(!ecoll[0]){StopAlert (MEMORY_ALRT);return line_number;}
  for(i=0;i<nat;i++)
    ecoll[i+1]=ecoll[i]+nat+1;
  for(i=0;i<nat2;i++)
    ecoll[0][i]=-1;

  icoll=(well_type **)malloc((nat+1)*sizeof(well_type *));
  if(!icoll){StopAlert (MEMORY_ALRT);return line_number;}
  icoll[0]=(well_type *)malloc(nat2*sizeof(well_type));
  if(!icoll[0]){StopAlert (MEMORY_ALRT);return line_number;}
  for(i=0;i<nat;i++)
    icoll[i+1]=icoll[i]+nat+1;
  for(i=0;i<nat2;i++)
    icoll[0][i]=-1;


  nen=0;
  nen1=ntot;
  for(i=1;i<=nat;i++)
    for(j=1;j<=i;j++)
      {
	if(coldata[i][j])
	  {
	    l=coldata[i][j][0];
            next=-1;
	    for(k=1;k<l;k+=2)
	      {
		if(k==1)
		  {
                    nen1--;
                    num=nen1;
		  }
                else
		  {
		    num=nen;
		    nen++;
		  }
		if(k==l-2)
		  prev=-1;
                else
		  prev=nen;
		init_coll(num,prev,next,sam[i].m,sam[j].m,coldata[i][j][k+1],coldata[i][j][k],0);
		next=num;
	      }
	    ecoll[i][j]=next;
            ecoll[j][i]=next;
	  }
	else
	  {
	    nen1--;
            ecoll[i][j]=nen1;
            ecoll[j][i]=nen1;
            init_coll(nen1,-1,-1,sam[i].m,sam[j].m,dblarg1,sam[i].s+sam[j].s,0);
	  }
      }
  
  if(is_en)
    for(i=1;i<=nat;i++)/*ncoll*/
      for(j=1;j<=i;j++)
	{
	  double d=sam[i].s+sam[j].s;
	  double d2=d*d;
	  nen1--;
	  ncoll[i][j]=nen1;
	  ncoll[j][i]=nen1;
	  {
	    int ii=ecoll[i][j];
	    while(ii>-1){
	      if(d2>=coll[ii].dd){
		d=sqrt(coll[ii].dd);
		break;
	      }		
	      ii=coll[ii].next;
	    }
	  }
	  init_coll(nen1,-1,-1,sam[i].m, sam[j].m,dblarg1,d,0);
	}

  for(i=1;i<=nat;i++)
    for(j=1;j<=i;j++)
      if(bonddata[i][j])
	{
	  if(bonddata[i][j]<bonds)
	    {
	      l=bonddata[i][j][0];
	      unstable=l&1;
	      l=l|1;
	      next=-1;
	      for(k=1;k<l;k+=2)
		{
		  if((k==1)||((k==l-2)&&(!unstable)))
		    {
		      nen1--;
		      num=nen1;
		    }
		  else
		    {
		      
		      num=nen;
		      nen++;
		    }
		  
		  if(k==l-2)
		    {
		      prev=-1;
		      if(unstable)
			en=bonddata[i][j][k+1];
		      else
			en=dblarg1;
		    }
		  else
		    {
		      en=bonddata[i][j][k+1];
		      prev=nen;
		    }
		  if((k==l-4)&&(!unstable))
		    prev=nen1-1;
		  init_coll(num,prev,next,sam[i].m,sam[j].m,en,bonddata[i][j][k],-1);
		  next=num;
		}
	      icoll[i][j]=next;
	      icoll[j][i]=next;
	    }
	  else
	    {
	      nen1--;
	      init_coll(nen1,nen1-1,-1,sam[i].m,sam[j].m,dblarg1,sam[i].s+sam[j].s,-1);
	      nen1--;
	      icoll[i][j]=nen1;
	      icoll[j][i]=nen1;
	      init_coll(nen1,-1,nen+1,sam[i].m,sam[j].m,dblarg1,sam[i].b+sam[j].b,-1);
	      /* bond collision types has -1 in reaction field even if no reaction happen */
	    }
	}
  

  for(i=1;i<=nat;i++)
    for(j=1;j<=i;j++)
      {
	next=ecoll[i][j];
        coll[next].etot=0;
	if(is_en){
	  next=ncoll[i][j];
	  coll[next].etot=0;
	}
	next=icoll[i][j];
	if(next>-1)
	  coll[next].etot=0;
      }

  /*scanf("%d",&i);*/
  for(k=1;k<=nrt;k++)
    if(react[k].bond>=0)
      {
	i=react[k].new1;
	j=react[k].new2;
	num=icoll[i][j];
	if(num<0)react[k].bond=0;
	if(react[k].bond)
	  {
	    if(react[k].dd>coll[num].dd)
	      react[k].bond=0;
	    else
	      {
		next=coll[num].next;
		while(next>-1)
		  {
		    if(react[k].dd>coll[next].dd)
		      {

			react[k].in=next;
			break;
		      }
		    next=coll[next].next;  
		  }
		if(next<0)react[k].bond=0;
		else
		  {
		    
		    if(coll[num].eo==-dblarg1)
		      coll[num].etot=-react[k].eo;
		    else
		      {
			coll[num].react=-k-1; /* reverese reaction happens if .react is less then -1 */
			next=ecoll[react[k].old1][react[k].old2];
			while(next>-1)
			  {
			    if(coll[num].dd >=coll[next].dd)
			      {
				react[k].out=next;
				break;
			      }
			    next=coll[next].next;
			  }
		      }
		  }
	      }
	  }
	if((react[k].in>-1)||(!(react[k].bond)))
	  {
	    i=react[k].old1;
	    j=react[k].old2;
	    next=ecoll[i][j];
	    while(next>-1)
	      {
		if(react[k].dd>=coll[next].dd)
		  {
		    if(react[k].dd>coll[next].dd)
		      {
			prev=coll[next].prev;
			num=nen;
			nen++;
			init_coll(num,prev,next,sam[i].m,sam[j].m,(double)0,sqrt(react[k].dd),0);
			if(!react[k].bond)react[k].in=next;
			coll[next].prev=num;
			if(prev==-1)
			  {
			    ecoll[i][j]=num;
			    ecoll[j][i]=num;
			    coll[num].etot=0;
			  }
			else
			  {
			    coll[prev].next=num;
			  }
		      }
		    else
		      {
			num=next;
			next=coll[next].next;
			if(next<=-1){printf("error\n");return 0;}			
			if(!react[k].bond)react[k].in=next;
			
		    }
		    coll[num].react=k;
		    break;
		  }
		next=coll[next].next;
	      }
	  }
      }
    else /* irreversible reactions of breaking bonds created when bond is breakable 
	    but no bond-forming reaction corresponing to input types is specified */
      {
	react[k].bond=1;
	num=icoll[react[k].new1][react[k].new2];
	coll[num].react=-k-1; /* reverese reaction happens if .react is less then -1 */
	next=ecoll[react[k].old1][react[k].old2];
	while(next>-1)
	  {
	    if(coll[num].dd >=coll[next].dd)
	      {
		react[k].out=next;
		break;
	      }
	    next=coll[next].next;
	  }
      }
  

  /*printf("step1\n");*/
  for(i=1;i<=nat;i++)
    for(j=1;j<=i;j++)
      { 
	num=ecoll[i][j];

	while(num>-1)
	  {		
	    next=coll[num].next;
	    if(next>-1)
	      {
		  coll[next].etot=coll[num].etot+coll[num].eo;
/*	printf("%d %lf\n",num,coll[num].etot);*/
	      }
		num=next;
	  }
      }
/*printf("step2\n");*/  
  for(i=1;i<=nat;i++)
    for(j=1;j<=i;j++)
      {
	num=icoll[i][j];
	while(num>-1)
	  {
	    next=coll[num].next;
	    if(next>-1)
	      {
		en=coll[num].eo;
		if(en==-dblarg1)en=0;
		coll[next].etot=coll[num].etot+en;
	      }
	    num=next;
	  }
	num=icoll[i][j];
	if(num>-1)coll[num].etot=0;
      }
/*printf("step3\n");*/
  if(is_en)
    for(i=1;i<=nat;i++)
      for(j=1;j<=i;j++)
	{ 
	  num=ncoll[i][j];
	  
	  while(num>-1)
	    {		
	      next=coll[num].next;
	      if(next>-1)
		{
		  coll[next].etot=coll[num].etot+coll[num].eo;
		  /*	printf("%d %lf\n",num,coll[num].etot);*/
		}
	      num=next;
	    }
	}
}

make_key_system(int first_key, unsigned char * buf,int file_length)
{  
  unsigned char * datfile, *nextline= buf;
  int i,i1,i2,i3,j,k,ix,iy,iz,lbr,lbw,l,l0,ares,nneib,k1;
  double r0,d,dx,dy,dz,vel0,vv;
  double enr,enw,maxrb;
  int nr,nc,nl,lp,lo,no,ls,ns,nw,istart;
  int err;
  double ccell, L[3];
  int ndim;
  int current_key=first_key;
  int numcol;
  int numwell=0;
  int numbondwell=0;
  int numunstable=0;
  int numword;
  int numbond=0;
  int next_key;
  int lbt=0;/*length of bond table*/
  int lct=0;/*length of collision table*/
  double *storage, *top, *dummy, *bonds=0;
  double *perm_bonds;
  int nperm_bonds=0;
  double ***coldata;
  double ***bonddata;
  double coord_shift[3]={0.0,0.0,0.0};
  ReactionData * react0;
  ReactionData * react1;
  printf("dx,dy,dz=?\n");
  scanf("%lf %lf %lf",coord_shift,coord_shift+1,coord_shift+2);
  nrt=0;
  storage=(double *)malloc(file_length*sizeof(double));
  if(!storage){StopAlert (MEMORY_ALRT);return line_number;}
  dummy=storage;
  while(current_key)
    {
      switch (current_key){
	case SYS_SIZE :
	  {
	    printf("%s\n",keywords[current_key]);
	    datfile=nextline;if(!(nextline=next_line(datfile)))return line_number;
	    /*     What is system size */
	    ndim=0;
	      
		while(is_word(datfile))
		  {
		    sscanf(datfile,"%lf",storage+ndim);
                    ndim++;
		    if(!(datfile=next_word(datfile)))break;
		  }
	    if((ndim<2)||(ndim>3))return line_number;
	    for(i=0;i<ndim;i++)
	      {
		if(dummy[i]<=0)return line_number;
                L[i]=dummy[i];
		printf("%lf\n",L[i]);
	      }
	    datfile=nextline;
	    if(!(nextline=next_line(datfile)))return line_number;
	    next_key=iskeyword(datfile);
	    if(next_key<=0)return line_number;
	    else current_key=next_key;
            break;
	  }
	case NUM_ATOMS:
	  {
	    printf("%s\n",keywords[current_key]);
	    datfile=nextline;if(!(nextline=next_line(datfile)))return line_number;
            /* what is number of atoms */
	    sscanf(datfile,"%lf",dummy);
            n1=dummy[0];
            if((n1<1)||(n1!=dummy[0]))return line_number;
	    datfile=nextline;
	    if(!(nextline=next_line(datfile)))return line_number;
	    next_key=iskeyword(datfile);
	    if(next_key<=0)return line_number;
	    else current_key=next_key;
	    if(!(a=(atom *)malloc((n1+1)*sizeof(atom))))
	      {StopAlert (MEMORY_ALRT);return line_number;}
	      for(i=0;i<n1;i++)
		a[i].c=0;
	    printf("NUM_ATOMS=%d\n",n1);
	    set_write_param(0,n1,0); /* setting parameters for text writing */
	    n=n1-1;
            break;
	  }
	case TYPE_ATOMS: 
	  {

	    printf("%s\n",keywords[current_key]);
            nat=0;
	    maxrb=0;
            do
	      {
		numword=0;
		datfile=nextline;if(!(nextline=next_line(datfile)))return line_number;
		next_key=iskeyword(datfile);
		if(next_key<0)return line_number;
                if((next_key>0)&&(!nat))return line_number;
                if(!next_key)
		  {
		    /* what is type, mass, small radius , big radius */
		    numword=0;
		    while(is_word(datfile))
		      {
			sscanf(datfile,"%lf",dummy+nat+numword);
			numword++;
			if(!(datfile=next_word(datfile)))break;
		      }
		    if((numword<3)||(numword>4))return line_number;
		    if(dummy[nat]!=(int)dummy[nat])return line_number;
		    if(numword==3)dummy[nat+3]=dummy[nat+2];
		    if(dummy[nat+3]<dummy[nat+2])return line_number;
		    nat+=4;
		  }
	      }while(!next_key);
            nat/=4;
	    if(!(sam=(atom *)malloc((nat+1)*sizeof(atom))))
	      {StopAlert (MEMORY_ALRT);return line_number;}
	    for(i=1;i<=nat;i++) /*fix it later 4*/
	      sam[i].c=0;

	    for (i=1;i<=nat;i++)
	      {
		j=dummy[(i-1)*4];
		if((j>nat)||(j<1))return line_number; /*fix it later 4*/
                if(sam[j].c)return line_number; /*fix it later 4*/
		sam[j].m=dummy[(i-1)*4+1];
		sam[j].s=dummy[(i-1)*4+2];
		sam[j].b=dummy[(i-1)*4+3];
		sam[j].c=i;
		sam[j].origc=sam[i].c;
		sam[j].hb=-1; sam[j].gid=-1; sam[j].rid=-1;
		sam[j].hb_a1=-1; sam[j].hb_a2=-1;
		sam[j].hb_asso=0;
		sam[j].hb_p1=-1; sam[j].hb_p2=-1;
		sam[i].r=o;
		sam[i].v=o;
		sam[i].t=0.0;
		sam[i].qt=0.0;
		sam[i].i.x.i=0;
		sam[i].i.y.i=0;
		sam[i].i.z.i=0;
		if(sam[i].b>maxrb)maxrb=sam[i].b;
	      }
            maxrb*=2; 
	    for (i=1;i<=nat;i++)
	      printf("%d %d %lf %lf %lf\n",i,sam[i].c,sam[i].m,sam[i].s,sam[i].b);

	    
            coldata=(double ***)malloc((nat+1)*sizeof(double **));
	    if(!coldata){StopAlert (MEMORY_ALRT);return line_number;}
            numcol=nat*(nat+1)/2;
            coldata[0]=(double **)malloc((numcol+1)*sizeof(double *));
	    if(!coldata[0]){StopAlert (MEMORY_ALRT);return line_number;}
            
	    for(i=0;i<nat;i++)
            coldata[i+1]=coldata[i]+i;

	    for(i=0;i<=numcol;i++)
            coldata[0][i]=0;

            bonddata=(double ***)malloc((nat+1)*sizeof(double **));
	    if(!coldata){StopAlert (MEMORY_ALRT);return line_number;}
            bonddata[0]=(double **)malloc((numcol+1)*sizeof(double *));
	    if(!coldata[0]){StopAlert (MEMORY_ALRT);return line_number;}
            
	    for(i=0;i<nat;i++)
            bonddata[i+1]=bonddata[i]+i;

	    for(i=0;i<=numcol;i++)
            bonddata[0][i]=0;
            top=storage;


	    current_key=next_key;
            break;
	  }
	case NONEL_COL:
	case EL_COL:
	  {
	    printf("%s\n",keywords[current_key]);
	    do
	      {
		datfile=nextline;if(!(nextline=next_line(datfile)))return line_number;
		next_key=iskeyword(datfile);
		if(next_key<0)return line_number;
                if(!next_key)
		  {
                    double a=0;
		    numword=0;
/* type1 type2 hard_core1 [softcore1 energy1[softcore 2 energy2...]] */
		    while(is_word(datfile))
		      {
			sscanf(datfile,"%lf",top+numword);
			numword++;
			if(!(datfile=next_word(datfile)))break;
		      }
		    if((numword<3)||(!(numword&1)))return line_number;
                    if((current_key==EL_COL)&&(numword>3))return line_number;
		    i=top[0];
		    if(i!=top[0])return line_number;
		    j=top[1];
                    if(j!=top[1])return line_number;
		    if(j>i){k=i;i=j;j=k;}
		    if(coldata[i][j])return line_number;
		    coldata[i][j]=top;
                    top[0]=numword;
		    top[1]=top[2];
		    top[2]=dblarg1;
                    for(k=1;k<numword;k+=2)
		      {
			if(top[k]<=a)return line_number;
			a=top[k];
		      }
		    if(maxrb<a)maxrb=a;
		    top+=numword;
                    bonds=top;
		    numwell+=numword>>1;
		  }
	      }while(!next_key);
	  current_key=next_key;
	  break;
	  }
	case LINK_PAIRS:
	  {
	    printf("%s\n",keywords[current_key]);
	    do
	      {
		datfile=nextline;if(!(nextline=next_line(datfile)))return line_number;
		next_key=iskeyword(datfile);
		if(next_key<0)return line_number;
                if(!next_key)
		  {
                    double a=0;
		    numword=0;
/* type1 type2 hard_core1 [softcore1 energy1[softcore 2 energy2...]] hardcore2 [energy of breaking] */
		    while(is_word(datfile))
		      {
			sscanf(datfile,"%lf",top+numword);
			numword++;
			if(!(datfile=next_word(datfile)))break;
		      }
		    if(numword<4)return line_number;
		    i=top[0];
		    if(i!=top[0])return line_number;
		    j=top[1];
                    if(j!=top[1])return line_number;
		    if(j>i){k=i;i=j;j=k;}
		    if(bonddata[i][j])return line_number;
		    bonddata[i][j]=top;
                    top[0]=numword;
		    top[1]=top[2];
		    top[2]=dblarg1;

                    for(k=1;k<numword;k+=2)
		      {
			if(top[k]<=a)return line_number;
			a=top[k];
		      }
/* if the bond is breakable it should be inter than the hardcore */
                    if((numword&1)&&(a<coldata[i][j][1]))return line_number;
		    if(maxrb<a)maxrb=a;
		    top+=numword;
                    bonds=top;
		    numbondwell+=numword>>1;
                    numunstable+=numword&1;
		  }
	      }while(!next_key);
		    
	    if(numunstable)
	      {
		react0=(ReactionData *)malloc((numunstable+1)*sizeof(ReactionData));
		k=0;
		for(i=1;i<=nat;i++)
		  for(j=1;j<=i;j++)
		    if(bonddata[i][j])
		      {
			numword=bonddata[i][j][0];
			if(numword&1)
			  {
			    k++;
			    react0[k].old1=i;
			    react0[k].old2=j;
			    react0[k].new1=i;
			    react0[k].new2=j;
			    react0[k].bond=1;
			    react0[k].dd=bonddata[i][j][numword-2];
			    react0[k].dd*=react0[k].dd;
			    react0[k].eo=bonddata[i][j][numword-1];
			    react0[k].in=-1;
			    react0[k].out =-1;
			  }
		      }
	      }
	    current_key=next_key;
	    break;
	  }
	case REACT:
	  {
	    printf("%s\n",keywords[current_key]);
	    dummy=top;
            nrt=0;
            do
	      {
		numword=0;
		datfile=nextline;if(!(nextline=next_line(datfile)))return line_number;
		next_key=iskeyword(datfile);
		if(next_key<0)return line_number;
                if(!next_key)
		  {
/* old1 old2 new1 new2 [bond [radius [energy]]] */
		    int old1,old2,new1,new2;
		    numword=0;
		    while(is_word(datfile))
		      {
			sscanf(datfile,"%lf",dummy+nrt+numword);
			numword++;
			if(!(datfile=next_word(datfile)))break;
		      }
		    if((numword<4)||(numword>7))return line_number;
                    if(numword==4)dummy[numword]=0;
                    for(i=0;i<5;i++)
		      if(dummy[nrt+i]!=(int)dummy[nrt+i])return line_number;
		    old1=i=dummy[nrt];
		    old2=j=dummy[nrt+1];
                    new1=dummy[nrt+2];
                    new2=dummy[nrt+3];
                    if(sam[old1].m!=sam[new1].m)return line_number;
                    if(sam[old2].m!=sam[new2].m)return line_number;
		    if(j>i){k=i;i=j;j=k;}
		    /* by default, reaction radius and energy are taken from the
		       external non-ellastic collision, or from sam.b */
		    if((numword==5)||(numword==6))
		      {
			if((!coldata[i][j])||((coldata[i][j])&&(coldata[i][j][0]==3)))
			  {
			    dummy[nrt+6]=0;
			    if(numword==5)dummy[nrt+5]=sam[i].b+sam[j].b;
			  }
			else
                          {
			    int k=coldata[i][j][0];
			    dummy[nrt+6]=coldata[i][j][k-1];
			    if(numword==5)dummy[nrt+5]=coldata[i][j][k-2];
			  }
		      }
		    if(numword>=6)
		      {

			/* if radius of reaction is smaller than hardcore, reaction cannot happpen */
			if(coldata[i][j])
			  {
			    if(dummy[nrt+5]<=coldata[i][j][1])return line_number;
			  }
			else if(dummy[nrt+5]<=sam[i].s+sam[j].s)return line_number;
		      }
		    nrt+=7;
		  }
	      }while(!next_key);
	    nrt/=7;
	    react1=(ReactionData *)malloc((nrt+1)*sizeof(ReactionData));
	    if(!react1){StopAlert (MEMORY_ALRT);return line_number;}      
	    for (i=1;i<=nrt;i++)
	      {
		react1[i].old1=dummy[(i-1)*7];
		react1[i].old2=dummy[(i-1)*7+1];
		react1[i].new1=dummy[(i-1)*7+2];
		react1[i].new2=dummy[(i-1)*7+3];
		for(j=1;j<i;j++)
		  if(((react1[j].old1==react1[i].old1)&&(react1[j].old2==react1[i].old2))
		     ||((react1[j].old1==react1[i].old2)&&(react1[j].old2==react1[i].old1)))
		    {
		      printf("Multiple Definition of Reaction %d+%d->\n",react1[j].old1,react1[j].old2);
		      return line_number;
		    }
		react1[i].bond=dummy[(i-1)*7+4];
		react1[i].dd=dummy[(i-1)*7+5];
                if(maxrb<react1[i].dd)maxrb=react1[i].dd;
		react1[i].dd*=react1[i].dd;
		react1[i].eo=dummy[(i-1)*7+6];
                react1[i].in=-1;
                react1[i].out =-1;
	      }
	    for (i=1;i<=nrt;i++)
	      printf("%d %d %d %d %d %lf %lf\n",react1[i].old1,react1[i].old2,
		     react1[i].new1,react1[i].new2,react1[i].bond,react1[i].dd,react1[i].eo);

	    current_key=next_key;
            break;
	  }

	case LIST_ATOMS:
	  {
	    int na=0;
	    printf("%s\n",keywords[current_key]);
	    set_new_bounds_2(L,maxrb,ndim);
	    dummy=top;
            do
	      {
                int nd=3;
                iatom * b;
		numword=0;
		if(!nextline)
		  {if(na==n1)goto finish;
		  else return line_number;}
		
		datfile=nextline;
		nextline=next_line(datfile);
		next_key=iskeyword(datfile);
		if(next_key<0)return line_number;
                if((next_key>0)&&(n1!=na))return line_number;
                if(!next_key)
		  {
/* number type x y [z] v_x v_y [v_z]  */
                    if(na==n1)return line_number;
		    numword=0;
		    while(is_word(datfile))
		      {
			sscanf(datfile,"%lf",dummy+numword);
			numword++;
			if(!(datfile=next_word(datfile)))break;
		      }
		    if(!(((numword==6)&&(ndim==2))||(numword==8)))return line_number;
                    i=dummy[0];
		    if(dummy[0]!=i)return line_number;
                    j=dummy[1];
		    if(dummy[1]!=j)return line_number;
                    i--;
		    if((i<0)||(i>=n1)||a[i].c)return line_number;
		    if((j<1)||(j>nat))return line_number;
                    a[i]=sam[j];
                    a[i].c=j;
                    b=(iatom *)(a+i); 
                    if(numword==6)nd=2;
		    for(k=0;k<ndim;k++)
		      {
			b->r[k]=dummy[2+k]+coord_shift[k];
			if(b->r[k]>bound[k].length)b->r[k]-=bound[k].length;
			if(b->r[k]<0)b->r[k]+=bound[k].length;
			if(b->r[k]>bound[k].length)return line_number;
			if(b->r[k]<0)return line_number;
			b->i[k].i=(int)(b->r[k]/bound[k].dl);
			b->v[k]=dummy[2+nd+k];
		      }
		    if(a[i].m >= m_max){
		      a[i].v.x =0;
		      a[i].v.y =0;
                      a[i].v.z =0;
		     // printf("imobilize: %ld:3 %20.18lf %20.18lf %20.18lf\n", i, a[i].v.x, a[i].v.y, a[i].v.z);
		    }
		  }
		na++;
	      }while(!next_key);
	    current_key=next_key;
	    break;
	  }
	case LIST_BONDS:
	  {
	    printf("%s\n",keywords[current_key]);
	    numbond=0;
	    do
	      {
		if(!nextline)goto finish;
		datfile=nextline;
		nextline=next_line(datfile);
		next_key=iskeyword(datfile);
		if(next_key<0)
		  return line_number;
                if(!next_key)
		  {
                    double a=0;
		    numword=0;
		    /* atom1  atom2 */
		    while(is_word(datfile))
		      {
			sscanf(datfile,"%lf",top+numword);
			numword++;
			if(!(datfile=next_word(datfile)))break;
		      }
		    if(numword<2)return line_number;
		    i=top[0];
		    if(i!=top[0])return line_number;
		    for(k=numword-1;k>=1;k--)
		      {
			j=top[k];
			if(j!=top[k])return line_number;                  
			if((i<1)||(i>n1)||(j<1)||(j>n1))return line_number;
                        top[2*k-2]=i-1;
			top[2*k-1]=j-1;
			numbond++;
		      }
		    top+=2*(numword-1);
		    perm_bonds = top;
		  }
	      }while(!next_key);
	    current_key=next_key;
	    break;
	  }
      case LIST_PERM_BONDS:{
	printf("%s\n",keywords[current_key]);
	nperm_bonds=0;
	do{
	  if(!nextline)goto finish;
	  datfile=nextline;
	  nextline=next_line(datfile);
	  next_key=iskeyword(datfile);
	  if(next_key<0)
	    return line_number;
	  if(!next_key){
	    numword=0;
	    while(is_word(datfile)){
	      sscanf(datfile,"%lf",top+numword);
	      numword++;
	      if(!(datfile=next_word(datfile)))break;
	    }
	    if(numword!=4)return line_number;
	    nperm_bonds++;
	    i=top[0];
	    j=top[1];
	    if(top[2]!=(int)top[2] ||
	       top[3]!=(int)top[3]){
	      return line_number;
	    }
	    a[i-1].origc = (int)top[2];
	    a[j-1].origc = (int)top[3];
	    top[0] = i-1;
	    top[1] = j-1;
	    top+=numword;
	  }
	}while(!next_key);
	current_key = next_key;
	break;
      }
      
      case NUM_BONDS:
	{
	  dummy=top;
	  printf("%s\n",keywords[current_key]);
	  if(!nextline)goto finish;	    
	  datfile=nextline;
	  nextline=next_line(datfile);
	  /* what is maximal number of bonds */
	  sscanf(datfile,"%lf",dummy);
	  lbt=dummy[0];
	  if((lbt<1)||(lbt!=dummy[0]))return line_number;
	  if(!nextline)goto finish;	    
	  datfile=nextline;
	  nextline=next_line(datfile);
	  next_key=iskeyword(datfile);
	  if(next_key<=0)return line_number;
	  else current_key=next_key;
	  break;
	}
      case LIST_PARAM:
	  {
	    dummy=top;
	    printf("%s\n",keywords[current_key]);
	    do
	      {
		if(!nextline)goto finish;
		datfile=nextline;
		nextline=next_line(datfile);
		next_key=iskeyword(datfile);
		if(next_key<0)return line_number;
                if(!next_key)
		  {
		    isparam(datfile);
		  }
	      }while(!next_key);
	  current_key=next_key;
	  break;
	  }

	  
      case COL_TABLE:
	{
	  dummy=top;
	  printf("%s\n",keywords[current_key]);
	  if(!nextline)goto finish;	    
	  datfile=nextline;
	  nextline=next_line(datfile);
	  /* what is maximal number of bonds */
	  sscanf(datfile,"%lf",dummy);
	  lct=dummy[0];
	  if((lct<1)||(lct!=dummy[0]))return line_number;
	  if(!nextline)goto finish;	    
	  datfile=nextline;
	  nextline=next_line(datfile);
	  next_key=iskeyword(datfile);
	  if(next_key<=0)return line_number;
	  else current_key=next_key;
	  break;
	}
	
      case HB_LIST:
	{
	  dummy=top;
	  printf("%s\n",keywords[current_key]);
	  is_hb=1;
	  do{
	    if(!nextline)goto finish;
	    datfile=nextline;
	    nextline=next_line(datfile);
	    next_key=iskeyword(datfile);
	    if(next_key<0)
	      return line_number;
	    if(!next_key){
	      numword=0;
	      while(is_word(datfile)){
		sscanf(datfile,"%lf",top+numword);
		numword++;
		if(!(datfile=next_word(datfile)))break;
	      }
	      if(numword!=4 && numword!=3 && numword!=2 && numword!=7)return line_number;
	      if(top[0]!=(int)top[0]||
		 top[1]!=(int)top[1])return line_number;
	      i=top[0];
	      if(numword!=7) 
		a[i-1].hb   = numword - 2;
	      else 
		a[i-1].hb   = numword - 5;
	      a[i-1].gid  = top[1];
	      if(a[i-1].hb==1){
		a[i-1].hb_a1 = top[2]-1;
		a[i-1].hb_a2 = -1;
		{
		  int ia=top[2]-1;
		  a[ia].hb_asso=1;
		  if(a[ia].hb_p1<0) a[ia].hb_p1=i-1;
		  else a[ia].hb_p2=i-1;
		}
	      }
	      else if(a[i-1].hb==2){
		a[i-1].hb_a1 = top[2]-1;
		a[i-1].hb_a2 = top[3]-1;
		{
		  int ia=top[2]-1;
		  a[ia].hb_asso=1;
		  if(a[ia].hb_p1<0) a[ia].hb_p1=i-1;
		  else a[ia].hb_p2=i-1;
		  ia=top[3]-1;
		  a[ia].hb_asso=1;
		  if(a[ia].hb_p1<0) a[ia].hb_p1=i-1;
		  else a[ia].hb_p2=i-1;
		}
	      }
	      else{
		a[i-1].hb_a1=-1;
		a[i-1].hb_a2=-1;
	      }
	      top+=numword;
	    }
	  }while(!next_key);
	  current_key=next_key;
	  break;
	}

      case GID_LIST:
	{//atom_number GID
	  dummy=top;
	  printf("%s\n",keywords[current_key]);
	  is_en=1;
	  do{
	    if(!nextline)goto finish;
	    datfile=nextline;
	    nextline=next_line(datfile);
	    next_key=iskeyword(datfile);
	    if(next_key<0)
	      return line_number;
	    if(!next_key){
	      numword=0;
	      while(is_word(datfile)){
		sscanf(datfile,"%lf",top+numword);
		numword++;
		if(!(datfile=next_word(datfile)))break;
	      }
	      if(numword!=2) return line_number;
	      i=top[0];
	      if(a[i-1].rid<0) a[i-1].rid=(int)top[1];
	      else if(a[i-1].rid!=(int)top[1]) return line_number;
	    }
	  }while(!next_key);
	  current_key=next_key;
	  break;
	}
	
      default:
	{
	  printf("%s\n",keywords[current_key]);
	  return line_number;
	}
      }/* switch */
      
      
    }/* while (current_k) */
 finish:
  if(nrt||numunstable)
    {
      collp=(well_type *)malloc(n1*sizeof(well_type));
      if(!collp){nrt=numunstable=0;}
      collq=(well_type *)malloc(n1*sizeof(well_type));
      if(!collq){nrt=numunstable=0;}
      collr=(well_type *)malloc(n1*sizeof(well_type));
      if(!collr){nrt=numunstable=0;}
    }
  
  nrt=allocReact(react1,nrt,react0,numunstable);
  if(nrt<0)return line_number;
  if(!allocBonds(n1, numbond,nrt,lbt)){StopAlert (MEMORY_ALRT);return line_number;}
  
  if((make_bonds(numbond,bonds))<0)printf("error in bonds\n");
  else{       
    printf("number of bonds= %d\n",numbond);
  }
  
  if(nperm_bonds>0){
    if(!allocPerm()){StopAlert (MEMORY_ALRT);return line_number;}
    if((makePermBonds(nperm_bonds, perm_bonds))<0)printf("error in bonds\n");
    //makePermBonds(nperm_bonds, perm_bonds)
    else{
      printf("number of permanent bonds= %ld\n",nperm_bonds);
    }
  }
  
  printf("%ld %ld %ld %ld\n", (long)storage, (long)bonds, file_length,(long)top); 
  
  make_wells(coldata,numwell,bonddata,numbondwell,
	     bonds,numbond,a,n1,sam,nat);
  /*  printwells(icoll,nat);
      printwells(ecoll,nat); */
  free(storage);
  free(bonddata[0]);
  free(bonddata);  
  free(coldata[0]);
  free(coldata);  

  /*temperary*/
  /**/
  hb_dt=(double**)malloc(n1*sizeof(double*));
  hb_dt[0]=(double*)malloc((n1*(n1-1))/2*sizeof(double));
  for(i=0; i<(n1*(n1-1))/2; i++) hb_dt[0][i]=0;
  for(i=1; i<n1; i++) hb_dt[i]=hb_dt[i-1]+i-1;

  hb_dt_prev=(double**)malloc(n1*sizeof(double*));
  hb_dt_prev[0]=(double*)malloc((n1*(n1-1))/2*sizeof(double));
  for(i=0; i<(n1*(n1-1))/2; i++) hb_dt_prev[0][i]=0;
  for(i=1; i<n1; i++) hb_dt_prev[i]=hb_dt_prev[i-1]+i-1;
  
  hb_n=(int**)malloc(n1*sizeof(int*));
  hb_n[0]=(int*)malloc((n1*(n1-1))/2*sizeof(int));
  for(i=0; i<(n1*(n1-1))/2; i++) hb_n[0][i]=0;
  for(i=1; i<n1; i++) hb_n[i]=hb_n[i-1]+i-1;
  /*end temperary*/

  return 1;
}
atom * get_sample_atoms(){return sam;}
int get_atom_types(){return nat;}

/*temperary*/
/**/
void set_hb(int p, int q){
  int a,b;
  double t=get_time();
  if(p>q){
    a=p;
    b=q;
  }
  else{
    a=q;
    b=p;
  }
  hb_dt_prev[a][b]=t;
}

void break_hb(int p, int q){
  int a,b;
  double t=get_time();
  if(p>q){
    a=p;
    b=q;
  }
  else{
    a=q;
    b=p;
  }
  hb_dt[a][b]+=t-hb_dt_prev[a][b];
  hb_dt_prev[a][b]=0;
  hb_n[a][b]++;
}

void close_hb(atom* a){
  FILE* fp=fopen("bcp_hb","w");
  double t= get_time();
  int i,j;
  for(i=0; i<n1; i++)
    for(j=0; j<i; j++){
      if(hb_dt_prev[i][j]){
	hb_dt[i][j]+=t-hb_dt_prev[i][j];
	hb_n[i][j]++;
      }
      if(hb_n[i][j]){
	hb_dt[i][j]/=(double)hb_n[i][j];
	fprintf(fp, "%ld %ld %ld %lf\n",a[i].gid,a[j].gid,hb_n[i][j],hb_dt[i][j]);
      }
    }
  fclose(fp);
}

