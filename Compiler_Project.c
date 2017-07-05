//expr works
#include<stdio.h>
#include<string.h>
#define max 1000
char store[max];

FILE *fp;
int ptr=0;
int cptr=0;
char cs[max];

void next()
{ 
  cptr=0;
  while(store[ptr]!=' ' && store[ptr]!='\0'){
	cs[cptr]=store[ptr];
	ptr++; cptr++;
}
cs[cptr]='\0';
ptr++;
printf(" %s",cs);
}


int expr()
{   printf(" expr ");
    int isave=ptr-strlen(cs)-1;

    if( mmutable() )
    {
        next();
        if (!strcmp(cs,"=") || !strcmp(cs,"+=") || !strcmp(cs,"-=") || !strcmp(cs,"*=") || !strcmp(cs,"/=") || !strcmp(cs,"%=") )
        {
            next();
            if (simple_expr())return 1; else return 0;
        
        } 
		else 
		{
			ptr=isave;
    	    next();
    	    if (simple_expr()) return 1; else return 0;
		}
    }
	else return 0;
    
    return 1;
}

int simple_expr2()
	{printf(" sim_exp2 ");
 
	if(!strcmp(cs,"||"))
	{
		next();
		if (and_expr())
		{
			next(); int cslen=strlen(cs);
			if(simple_expr2()) return 1;
			else {ptr = ptr - cslen-1; return 1;}
		}
		else return 0;
	}
	else return 0;
}


int simple_expr()
{printf("sim_expr ");  
	
	if(and_expr())
	{
		next(); int cslen= strlen(cs);
		if (simple_expr2())
			return 1;
		else {ptr = ptr - cslen-1; return 1;}
	}
	else return 0;
return 1;
}

int and_expr2()
{ printf("and_exp2 ");  
	
	if(!strcmp(cs,"&&"))
	{
		next();
		if (unary_expr())
		{
			next(); int cslen= strlen(cs);
			if(and_expr2()) 
				return 1;
			else {ptr = ptr - cslen-1; return 1;}
		}
		else return 0;
	}
	else return 0;
}

int and_expr()
{ printf("and_exp ");  
	
	if (unary_expr())
	{
		next(); int cslen= strlen(cs);
		if (and_expr2())
			return 1;
		else {ptr = ptr - cslen-1; return 1;}
	}
	else return 0;
}


int unary_expr()
{ printf(" unary_expr ");
    int isave=ptr-strlen(cs);
    

    if( !strcmp(cs,"!")) 
    {	
        next();
        if(unary_expr()) 	return 1; else return 0;
    }
    else if (rel_expr()) return 1; else return 0;
    
    return 1;
}

int rel_expr()
{	
	printf(" rel_exp ");
    int isave=ptr-strlen(cs);
    if (sum_expr())
    {
        next();int cslen = strlen(cs);
        if(relop()) 
        {
            next(); 
            if(sum_expr()) return 1; else return 0;
        }
        else{ ptr = ptr - cslen-1 ; return 1;}
    }
    else 
    {
        ptr=isave;
        next();
        if (sum_expr()) return 1; else return 0;
    }
    return 1;
}

int relop()
{	printf(" relop ");
    if (!strcmp(cs,"<=") || !strcmp(cs,">=") || !strcmp(cs,"<") || !strcmp(cs,">") || !strcmp(cs,"==") || !strcmp(cs,"!=") )
{ return 1;}
 else return 0;
    return 1;
}

int sum_expr2()
{	printf(" sum_exp2 ");
	//printf(" se2%c %d ", store[ptr],ptr);
		
	
	 int isave;
   isave=ptr-strlen(cs);
	if (sumop())
	{   
		next();
		if (term())
		{
			next(); int cslen=strlen(cs);
			if (sum_expr2()) 
			return 1;
			else{ptr = ptr-cslen-1; return 1;}
		}
		else return 0;
	}
	else 
	return 0 ;
	 
}
				

int sum_expr()
{ printf("sum_exp ");
	 
	if (term())
	{	//printf("se%d", ptr);
		next(); int cslen=strlen(cs);
		if( sum_expr2()){ printf("%s",cs);
			return 1;}
		else {ptr=ptr-cslen-1; return 1;}
	}
	else return 0;
}


int sumop()
{printf("sumop ");
    if (!strcmp(cs,"+") || !strcmp(cs,"-") ) 
	{ 		return 1; }
	else return 0;
    return 1;
}

mulop()
{	printf("mulop ");
    if (!strcmp(cs,"*") || !strcmp(cs,"/") ) 
	{		return 1;}
 else return 0;
    return 1;
}

int term2()
{ printf(" term2 ");
	//printf(" t2%s " , cs);   
	
	 int isave;
   isave=ptr-strlen(cs);
	if (mulop())
	{
		next();
		if (factor())
		{
			next(); int cslen = strlen(cs);
			if (term2())
			  return 1;
			else {ptr = ptr - cslen-1; return 1;}
		}
		else{ return 0;}
	}
	else 
	{	
		return 0;
	}
	
}
				

int term()
{	printf(" term "); 
	
	if (factor())
	{
		next(); int cslen=strlen(cs);
		if( term2())
			return 1;
		else{ ptr = ptr-cslen-1; return 1;}
	}
	else return 0;
}



int mmutable()
{	printf("mmutable ");
    if (!strcmp(cs,"id"))
			return 1;
	 else return 0;
    return 1;
}

int immutable()
{	printf("immutable ");
    if (!strcmp(cs,"(")) 
    {
        next();
        if (expr())
        {
            next();
            if (!strcmp(cs,")"))
            {
			return 1;
            }
            else return 0;
        }
        else return 0;
    }
    else if (constant()) 
			return 1;
 else return 0;
return 1;
}


factor()
{ printf(" factor ");
    if (immutable() || mmutable()) 
			return 1;
   else return 0;
    return 1;
}




int constant()
{	printf("const ");
    if (!strcmp(cs,"NUMCONST") || (!strcmp(cs,"CHARCONST")) || (!strcmp(cs,"STRINGCONST")) || (!strcmp(cs,"true")) || (!strcmp(cs,"false")) )
    {
        return 1;
    }else return 0;
}



return_stmt()
{ printf("retstmt ");
    if (!strcmp(cs,"return"))
    {
        next();
        if(expr())
        {
            next();
            if(!strcmp(cs,";")) 
			return 1;
	    else return 0;
        }
        else if(!strcmp(cs,";")) 
			return 1;
             else return 0;
    }
    else return 0;
}

break_stmt()
{	printf("brk ");
    if (!strcmp(cs,"break"))
    {
        next();
        if(!strcmp(cs,";")) 
				return 1;
        else return 0;
    }
    else return 0;
    return 1;
}

int expr_stmt()
{
 	if(expr())
	{ next();
		if(!(strcmp(cs,";")))
		return 1;
		else return 0;
} else if(!(strcmp(cs,";")))
	return 1; else return 0; 
}
int stmt()
{	/*
	if(expr_stmt() || selection_stmt() || iteration_stmt() || return_stmt() || break_stmt() )
			return 1;
	else return 0;
	return 1;
	*/
}

int type_spec()
{	printf(" type_spec ");
	if(!strcmp(cs,"int") || !strcmp(cs, "float") || !strcmp(cs,"char"))
	{	
		
		return 1;
	}
	else{  return 0;}

return 1;
}
 
int decl_list2()
{	
	printf(" decl_list2");
	if (decl()) 
	{
		next();
		if( decl_list2()) 
			return 1;
		else {ptr-=strlen(cs);
			return 1;
			}
			
	}
	else return 0;

	
return 1;
}
	

int decl_list()
{	
	printf(" decl_list");
	if (decl()) 
	{
		next();
		if( decl_list2()) 
			return 1;
	        else {ptr-=strlen(cs); return 1;}
	}
	else return 0;
return 1;
}

			

//A3
int decl()
{ printf(" decl"); 

	if(var_decl() || expr())
	{	printf(" oo");	return 1;	}
	else{ return 0;}
return 1;
}


//A4
int var_decl()
{ 
  printf(" var_decl ");
   
  if(type_spec())
	{ next();
	  if(var_decl_list()){
		next(); printf(" vdlcs %s",cs);
		if(!strcmp(cs,";")){
			printf(" correct ");
			return 1; }else return 0;
	}else return 0;} 
else { 
	return 0;
}
return 1;
}
//A6
int var_decl_init()
{	printf("var_decl_init ");
		
		
		if(var_decl_id())
		{	return 1;
			
		}
		else return 0;
return 1;
}		

int var_decl_list2()
{		
	printf(" var_decl_list2 ");
	if(!(strcmp(cs,",")))
	{ 
		next();
		if( var_decl_init())
		{
			next();
			if (var_decl_list2())
				return 1;
		 	else {return 0; }
		}
		else return 0;
	} 
	else{ if(var_decl_init()) { return 1;} else return 0; } 
		return 1;
	}

int var_decl_list()
{	int cslen = strlen(cs);	
	printf(" var_decl_list ");
	if( var_decl_init())
	{
		next();
		
		if (var_decl_list2()){ printf(" true ");
			return 1;}
		else { ptr=(ptr-cslen); return 1; }
	}
	else return 0;
return 1;
}

		
int var_decl_id()
{  printf("var_decl_id");
	
	
	if(!strcmp(cs,"id"))
	{	return 1;}
	else return 0;

 return 1;
}

//A1
int program()
{	printf(" program ");
	if(decl_list())
	{	return 1;
	}
	else printf("\nERROR!\n");
	return 0;

return 1;
}



void main()
{  int i=0;
   for(i=0;i<10;i++)
	 store[i]='$';

  	//Read the file
	fp = fopen("file.txt", "r");
	
	
	//fgets(store, 100, fp);
	//printf("%s",store);
	printf("Enter no. of lines in the code: ");
	int num;
	scanf("%d",&num);
	printf("\n\n");
	for (i=0;i<num; i++)
	{
		ptr=0;
		fgets(store, 100, fp);
		
		printf("stream of tokens is :  %s\n",store);
		printf("Route:\n");		
		next();
		
		 if(program()) printf("\n\n SUCCESSFUL PARSING\n\n"); 
	}
	
	//next(); if(program()) printf("\n SUCCESSFUL PARSING"); 
	//for(i=0;i<10;i++)
	 //store[i]='$';
//printf("%s\n",store);

 	
//	fgets(store,100,fp); ptr=0;
//printf("%s\n",store); next();
//	if(program()) printf("\n SUCCESSFUL PARSING"); 
	
	
//}
	//if(program()) printf("Successful Parsing");
	//else printf("Fail! you ullu!"); 
}
