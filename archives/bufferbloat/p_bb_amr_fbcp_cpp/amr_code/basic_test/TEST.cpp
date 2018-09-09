/*----------------------------------------------------------------------------
 REVOLVE -- Checkpointing approaches  andreas griewank
Amr Radwan 
----------------------------------------------------------------------------*/

#ifndef _REVOLVE_H
#define _REVOLVE_H

#include <vector>


#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <cstring>
using namespace std;

#define checkup 10000
#define repsup 6400
#define MAXINT 2147483647

namespace ACTION
{
	enum action { advance, takeshot, restore, firsturn, youturn, terminate, error} ;
}



/** \enum action
Through an encoding of its return value REVOLVE asks the calling program to perform one of these 'actions', which we will 
   refer to as 'advance', 'takeshot', 'restore', 'firsturn' and 'youturn'  .
   There are two other return values, namely 'terminate'   and     'error'
   which indicate a regular or faulty termination of the calls 
   to REVOLVE.
   The action 'firsturn' includes a 'youturn', in that it requires  
     -advancing through the last time-step with recording 
      of intermediates                                              
     -initializing the adjoint values (possibly after               
      performing some IO)                                           
     -reversing the last time step using the record just written    
   The action 'firsturn' is obtained when the difference FINE-CAPO  
   has been reduced to 1 for the first time. 
*/

/** \class Checkpoint
The class Checkpoint contains the two vectors ch and ord_ch. All checkpoints are stored in ch and the sequence of inizies can be found in ord_ch.
\brief Basic class for all Checkpointing schedules
*/


class Checkpoint
{
	public:

	Checkpoint(int s) { snaps=s; ch.reserve(snaps); number_of_writes.reserve(snaps); number_of_reads.reserve(snaps); }
	
	vector <int> ch;
	vector <int> ord_ch;
	vector <int> number_of_writes;
	vector <int> number_of_reads;
	void print_ch(ostream &file) { file << endl; for(int i=0;i<snaps;i++) file << ch[i] << " "; }
	void print_ord_ch(ostream &file) { file << endl; for(int i=0;i<snaps;i++) file << ord_ch[i] << " "; }
	void init_ord_ch() { ord_ch.reserve(snaps); }
	
	int advances, takeshots, commands;	
	~Checkpoint() { ch.clear(); ord_ch.clear(); number_of_writes.clear(); number_of_reads.clear();};

	private:

	int snaps;
	
};



/** \class Schedule
Schedule is the basic class of all Checkpointing schedules. This class stores the number of snaps and the checkpoints that have to be stored.
\brief Basic class for all Checkpointing schedules
*/

class Schedule
{
	public:

	/** This constructor needs a given array. This array is the initialisation of ch.
	*/
	Schedule(int sn,Checkpoint *c);
	Schedule(int sn) { snaps=sn; }
	
	/** This function does not do anything but must be derived
	*/
	virtual ACTION::action revolve() {};  
	/** The necessary number of forward steps without recording is calculated by the function 
                      NUMFORW(STEPS,SNAPS)                          
	STEPS denotes the total number of time steps, i.e. FINE-CAPO     
   	during the first call of REVOLVE. When SNAPS is less than 1 an    
   	error message will be given and -1 is returned as value.  */
	
	int numforw(int steps, int snaps);
	/** This function is virtual.*/
	virtual int get_capo(){};	
	/** This function is virtual.*/
	virtual int get_fine(){};	
	/** This function is virtual.*/
	virtual int get_check() {};	
	/** This function is virtual.*/
	virtual void set_fine(int f){};  
	/** This function is virtual.*/
	virtual void set_capo(int c) {}; 
	/** This function is virtual.*/
	int get_snaps() { return snaps; }
	/** This function returns the pointer of a Checkpoint class.
//	*/
	Checkpoint *get_CP() { return checkpoint; }
//	vector <int> get_ch()   { return ch; }
	/** This function returns the number of advances. */
	int get_advances() { return checkpoint->advances; }
	/** This function returns the number of takeshots. */
	int get_shots() { return checkpoint->takeshots; }
	/** This function returns the number of commands. */
	int get_commands() { return checkpoint->commands; }
	/** This function returns the info.*/
	virtual int get_info(){ return info;}	
	
	
	~Schedule() { /*delete[] ch;*/ }

	protected:
	Checkpoint *checkpoint;   
	/** Number of snaps used are stored in snaps*/
	int snaps;   
	int info;
};


/** \class Online
Online inherates the basic class Schedule. This class is the basic class for all Online Checkpointing schedules. 
\brief Basic class for all Online Checkpointing Schedules
*/

class Online : public Schedule
{
	public:

	/** This constructor needs the number of snaps for the Schedule Constructor and a bool parameter. */
	Online(int sn,Checkpoint *c,bool o);
	/** This is the Copy Constructor*/
	Online(Online &o);

	virtual ACTION::action revolve() {};
	/** This function returns the index of the last stored checkpoint.*/
	int get_check() { return check; }
	int get_capo()  { return capo; }
	virtual int get_fine() {};
	/** This function returns the variable output.*/
	bool get_output()      { return output; }
	void set_capo(int c) { capo=c; }

	~Online();

	protected:

	/** check is last stored checkpoint*/
	int check;
	/** output=true means that special information is printed on the screen */
	bool output;
	/** capo is the temporary fine */
	int capo;

};



/**
\class Online_r2 
This class creates a checkpoint schedule that is optimal over the range [0,(snaps+2)*(snaps+1)/2].
\brief class for Online Checkpointing Schedules for r=2
*/

class Online_r2 : public Online
{
	public:

	/** This constructor does not do anything. It only calls the basic constructor of Online.*/
	Online_r2(int sn,Checkpoint *c,bool o);
	/** Copy Constructor*/
	Online_r2(Online &o);

	/** The function revolve always returns the action the user has to do. During the forward integration only the actions advance and takeshot are returned. If the capo exceeds the maximal number of time steps, i.e. (snaps+2)*(snaps+1)/2, this function returns terminate.*/
	ACTION::action revolve();
	int get_check() { return check; }
	int get_capo()  { return capo; }
	int get_fine()  { return -1; }
	bool get_output()      { return output; }

	~Online_r2();

	private:

	int oldcapo_o,offset,incr,iter,t,oldind,old_f,ind;
	/**num_rep[i] is the repetion number*/
	vector <int> num_rep;

};


/**
\class Online_r3 
This class creates a checkpoint schedule that is quasi optimal over the range [(snaps+2)*(snaps+1)/2+1,(snaps+3)*(snaps+2)*(snaps+1)/6].
\brief class for Online Checkpointing Schedules for r=3
*/


class Online_r3 : public Online 
{
	public:

	/** This constructor needs an Online class. Usually this constructor is called after revolve of the class Online_r2 has returned terminate. */
	Online_r3(int sn,Checkpoint *c);
	Online_r3(Online_r3 &o) ;

	/** This function returns advance or takeshot during the forward integration. */
	ACTION::action revolve();

	/** This function returns the capo.*/
	int get_capo()  { return capo; }
	/** This function returns -1 because the end is not still reached.*/
	int get_fine()  { return -1; }

	/** This function returns the index of the checkpoint that can be replaced (Replacement condition). The argument number means that all checkpoints that fulfill the Replacement condition before number cannot be used.*/ 
	int choose_cp(int number);
	/** This function renews the array tdiff after a checkpoint was replaced*/
	void tdiff_akt();
	/** This function renews the array ord_ch of the class Online after a checkpoint was replaced*/
	void akt_cp();
	
	
	int get_tdiff_end(int i) { return tdiff_end[i]; }

	~Online_r3();

	protected:

	
	/** forward is number of time steps to advance*/
	int forward;
	/** ind_now is the temporary index of the checkpoints of the array ch3 that have to be taken*/ 
	int ind_now;
	/** cp is the Index of the checkpoint that can be replaced. To find the checkpoint out that can be replaced cp must be used in connection with ord_ch*/
	int cp;
	/** ch3 is the array of the final checkpoint distribution for r=3. These checkpoints must be taken!*/
	vector <int> ch3;
	/** tdiff[i] is the difference between the i.th and the i-1.th checkpoint*/
	vector <int> tdiff;
	/** tdiff_end is the array of differences for the final checkpoint distribution for r=3.*/
	vector <int> tdiff_end;
	/** cp_fest[i] defines if the i.th checkpoint can be overwritten or not.*/
	vector <bool> cp_fest;
};




/**
\class Arevolve
This class creates a checkpoint schedule that uses an heuristic approach for a checkpoint to be replaced. This class is usually called after another Onlie Checkpointing class has exceeds its maximum number of time steps.
\brief class for Online Checkpointing Schedules 
*/

class Arevolve : public Online
{
	public:

	/** Constructor that is called after an Online Checkpointing class has exceeded the max. number of time steps. */
	Arevolve(int sn,Checkpoint *c);
	/** Copy Constructor */
	Arevolve(Arevolve &o);

	/** This function returns the number of advance steps. This number depends on the the number of steps and snaps.*/
	int tmin(int steps, int snaps);
	/** This function calculates the number of advance steps for a given Checkpoint distribution. This distribution is stored in Schedule. */
	int sumtmin();
	/** This function will look for a checkpoint to be replaced for the condition of arevolve.*/
	int mintmin();
	/** This function returns the momental fine. */
	int get_fine() { return fine; }
	/** This function renews the array ord_ch of the class Online after a checkpoint was replaced.*/
	void akt_cp(int cp);
	
	void set_fine(int f) { fine=f; }

	/** This function returns advance or takeshot during the forward integration. */
	enum ACTION::action revolve();

	~Arevolve() { }
	
	private:

	int checkmax;
	int fine,oldfine,newcapo,oldcheck,oldcapo;

};

/**
\class Moin
This class creates a checkpoint schedule that minimizes the repetition rate for a checkpoint distribution. This class is called after 
the almost optimal Online Checkpointing approach has exceeded its maximum number of time steps hence beta(c,3).
\brief class for Online Checkpointing Schedules 
*/
class Moin : public Online
{
	public:

	/** Constructor that is called after an Online Checkpointing class has exceeded the max. number of time steps. */
	Moin(int sn,Checkpoint *c);
	/** Copy Constructor */
	Moin(Moin &o);
	
	bool is_dispensable(int *index);
	int get_lmin();
	void adjust_cp(int index);
	/** This function returns advance or takeshot during the forward integration. */
	enum ACTION::action revolve();

	~Moin() { }
	
	private:

	vector<int> l;
	vector<bool> d;
	bool start,start1,is_d;
	int forward,lmin,index_old;
	
};



/** \class Offline
Offline inherates the basic class Schedule. This class manages all Offline Checkpointing schedules. This class allows optimal Offline Checkpointing strategies if the number of time steps is a-priori known. This class also manages the optimal reversal of schedules resulting from Online Checkpointing
\brief Class for all Offline Checkpointing schedules
*/

class Offline : public Schedule
{
	public:

	/** This is the standard constructor that will be called if the number of time steps is a-priori known. */
	Offline(int st,int sn,Checkpoint *c);  
	/** This constructor will be called for the optimal Reversal of a schedule resulting from Online Checkpointing. */
	Offline(int sn,Checkpoint *c,Online *o,int f);	
	/** This constructor does not do anything and will usually not be called. */
	Offline(Schedule *o) ;    
	/** CopyConstructor */
	Offline(Offline &o);	 

	/**  Since REVOLVE involves only a few integer operations its run-time is truly negligible within any nontrivial application. The parameter SNAPS is selected by the user (possibly with the help of the routines EXPENSE and ADJUST described below ) and remains unchanged throughout. The pair (CAPO,FINE) always represents the initial and final state of the subsequence of time steps currently being traversed backwards. The conditions CHECK >= -1 and CAPO <= FINE are necessary and sufficient for a regular response of REVOLVE. If either condition is violated the value 'error' is returned. When CHECK =-1 and CAPO = FINE  then 'terminate' is returned as action value. This combination necessarily arises after a sufficiently large number of calls to REVOLVE, which depends only on the initial difference FINE-CAPO. The last parameter INFO determines how much information about the actions performed will be printed. When INFO =0 no  information is sent to standard output. When INFO > 0 REVOLVE produces an output that contains a prediction of the number of forward steps and of the factor by which the execution will slow down. When an error occurs, the return value of INFO contains information about the reason: INFO = 10: number of checkpoints stored exceeds CHECKUP, increase constant CHECKUP and recompile. INFO = 11: number of checkpoints stored exceeds SNAPS, ensure SNAPS greater than 0 and increase initial FINE. INFO = 12: error occurs in NUMFORW. INFO = 13: enhancement of FINE, SNAPS checkpoints stored,SNAPS must be increased. INFO = 14: number of SNAPS exceeds CHECKUP, increase constant CHECKUP and recompile. INFO = 15: number of REPS exceeds REPSUP, increase constant REPSUP and recompile. */

	ACTION::action revolve();
	
	int get_check() { return check; }
	int get_capo() { return capo; }
	int get_fine() { return fine; }
	int get_snaps() { return snaps; }
	int get_commands() { return checkpoint->commands; }
	int get_steps()    { return steps; }
	bool get_online()  { return online; }
	vector <int> get_num_ch() { return num_ch; }
	int get_num_ch(int i) { return num_ch[i]; }

	void set_fine(int f) { fine=f;}
	void set_capo(int c) { capo=c; }
	
	
	~Offline() { };

	private:

	int check, steps, oldsnaps, oldfine, capo, fine, turn,ind	;
	vector <int> num_ch;
	bool online,output;
};


/**
\class Revolve 
This class manages to create Schedules for Online or Offline Checkpointing. The user only needs to tell which Checkpointing Procedure he wants to use
\brief class to create Checkpoint Schedules
*/



class Revolve
{
	public:
	/** Constructor for Offline-Checkpointing*/
	Revolve(int st,int sn);
	/** Constructor for Multi-Stage Offline-Checkpointing*/
	Revolve(int st,int sn,int sn_ram);
	/** Constructor for Online-Checkpointing */
	Revolve(int sn);

	/**The calling sequence is REVOLVE(CHECK,CAPO,FINE,SNAPS,INFO) with the return value being one of the actions to be taken. The calling parameters are all integers with the following meaning: CHECK - number of checkpoint being written or retrieved. CAPO - beginning of subrange currently being processed. FINE - end of subrange currently being processed.SNAPS - upper bound on number of checkpoints taken. INFO - determines how much information will be printed and contains information about an error occured  */

 
	ACTION::action revolve(int* check,int* capo,int* fine,int snaps,int* info,bool *where_to_put);
	ACTION::action revolve(int* check,int* capo,int* fine,int snaps,int* info);
	ACTION::action revolve();

	/**The function ADJUST(STEPS) is provided. It can be used to determine a value of SNAPS so that the increase in spatial complexity equals approximately the increase in temporal complexity. For that ADJUST computes a return value satisfying SNAPS ~= log_4 (STEPS) because of the theory developed in the paper mentioned above. */
	int adjust(int steps);
	/** The auxiliary function MAXRANGE(SNAPS,REPS) returns the integer (SNAPS+REPS)!/(SNAPS!REPS!) provided SNAPS >=0, REPS >= 0. Otherwise there will be appropriate error messages and the value -1 will be returned. If the binomial expression is not representable as a  signed 4 byte integer, greater than 2^31-1, this maximal value is returned and a warning message printed.*/
	int maxrange(int ss, int tt);
	/** To choose an appropriated value of SNAPS the function EXPENSE(STEPS,SNAPS) estimates the run-time factor incurred by REVOLVE for a particular value of SNAPS. The ratio NUMFORW(STEPS,SNAPS)/STEPS is returned. This ratio corresponds to the run-time factor of the execution relative to the run-time of one forward time step.*/
	double expense(int steps, int snaps);
	/** The necessary number of forward steps without recording is calculated by the function NUMFORW(STEPS,SNAPS). STEPS denotes the total number of time steps, i.e. FINE-CAPO during the first call of REVOLVE. When SNAPS is less than 1 an error message will be given and -1 is returned as value.*/
	int numforw(int steps, int snaps) { return f->numforw(steps,snaps); }
	/** Turn starts the reversal of the schedule. This means that Online Checkpointing is finished. */
	void turn(int fine);
	
		
	vector <int> get_write_and_read_counts();
	int get_number_of_writes_i(int l, int c,int i);
	int get_number_of_reads_i(int l, int c,int i);
	
	
	int getadvances() { return f->get_advances(); }  
	int getcheck() { return check; }
	int getcheckram() { return indizes_ram[check]; }
	int getcheckrom() { return indizes_rom[check]; }
	int getcapo()  { return capo; }
	int getfine()  { return fine; }
	int getinfo()  { return info; }
	int getoldcapo() { return oldcapo; }
	bool getwhere() { return where_to_put; }
	void set_info(int inf) { info=inf; }
	void number_of_writes() { cout << endl; for(int i=0;i<snaps;i++) cout << checkpoint->number_of_writes[i] << " "; }
	void number_of_reads() { cout << endl; for(int i=0;i<snaps;i++) cout << checkpoint->number_of_reads[i] << " "; }
	
	int get_r(int steps,int snaps);
	int get_r();
	
	~Revolve() { delete f, delete checkpoint; }

	private:

	int check,capo,fine,snaps,info,steps,r,oldcapo;
	Schedule *f;
	bool online, multi, where_to_put;
	Checkpoint *checkpoint;
	vector <bool> where;
	vector <int> indizes_ram,indizes_rom;
};


#endif


#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <list>
#include <algorithm>

using namespace std;



/************************************************************************************************************************************
All routines of class Schedule
**********************************************************************************************************************************/


Schedule::Schedule(int sn,Checkpoint *c)
{
	snaps=sn;
	checkpoint=c;
	checkpoint->ch[0]=0;
}




int Schedule::numforw(int steps, int snaps)
{

	int reps, range, num;

	if (snaps < 1)
	{
		cout << " error occurs in numforw: snaps < 1 " << endl ;
		return -1;
	}
	if (snaps > checkup)
	{
		cout << " number of snaps = " << snaps << " exceeds checkup " << endl;
		cout << " redefine 'checkup'" << endl;
		return -1;
	}
	reps = 0;
	range = 1;
	while (range < steps)
	{
		reps += 1;
		range = range*(reps + snaps)/reps;
	}
	cout << " range = " << range << " reps= " <<  reps << endl;
	if (reps > repsup)
	{
		cout << " number of reps = " << reps << " exceeds repsup " << endl;
		cout << " redefine 'repsup' " << endl;
		return -1;
	}
	num = reps * steps - range*reps/(snaps+1);
	return num;


}


/*************************************************************************************************************************************
All routines of class Online
***************************************************************************************************************************************/


Online::Online(int sn,Checkpoint *c,bool o=false) : Schedule(sn,c)
{

	checkpoint->init_ord_ch(); //  ord_ch = new int[snaps];
	//cout <<"\n Vectors size = " << checkpoint->ord_ch.size() << endl;
	//for(int i=0;i<snaps;i++) cout << " " << checkpoint->ord_ch[i];
	output=o;
	
}

Online::Online(Online &o) : Schedule(o.get_snaps())
{
	//ord_ch = new int[snaps];
	checkpoint = o.get_CP();
	//checkpoint->init_ord_ch();
	output=false;
	//advances = o.get_advances();
	//takeshots = o.get_shots();
	//commands = o.get_commands();
	check = o.get_check();
	capo = o.get_capo();

}

Online::~Online()
{
	//delete [] ord_ch;
	//delete [] num_rep;
}

/*************************************************************************************************************************************
All routines of class Online_r2
**************************************************************************************************************************************/

Online_r2::Online_r2(int sn,Checkpoint *c,bool o=false) : Online(sn,c,o)
{
	num_rep.reserve(snaps);
	check=-1;
	capo=0;
}

ACTION::action Online_r2::revolve()
{
	//cout <<" check = "<< check << " ch[check] " << checkpoint->ch[check]<< " capo " << capo << endl; 
	checkpoint->commands++;
	if ((check == -1) || ((checkpoint->ch[check] != capo) && (capo <= snaps-1)))
		// condition for takeshot for r=1
	{

		oldcapo_o = capo;
		check += 1;
		checkpoint->ch[check] = capo;
		t = 0;
		if (snaps < 4)
		{
			for(int i=0;i<snaps;i++)
				num_rep[i] = 2;
			incr = 2;
			iter = 1;
			oldind = snaps-1;
		}
		else
		{
			iter = 1;
			incr = 1;
			oldind = 1;
			for(int i=0;i<snaps;i++)
			{
				num_rep[i] = 1;
				checkpoint->ord_ch[i] = i;
			}
			offset = snaps-1;
		}
		if (capo == snaps-1)
		{
			ind = 2;
			old_f = 1;
		}
		/*   	  cout <<" 2 *check %d ch[*check] %d *capo %d endl",*check,ch[*check],*capo); */
		
		// Increase the number of takeshots and the corresponding checkpoint
		checkpoint->takeshots++;
		//checkpoint->number_of_writes[check]++;
		
		return ACTION::takeshot;
	}
	else if (capo < snaps-1)
		// condition for advance for r=1
	{
		capo = oldcapo_o+1;
		checkpoint->advances++;
		return ACTION::advance;
	}
	else
		//Online-Checkpointing for r=2
	{
		if (checkpoint->ch[check] == capo)
			// condition for advance for r=2
		{
			switch (snaps)
			{
				case 1: capo = MAXINT-1;
					checkpoint->advances++;
					return ACTION::advance;
				case 2: capo = checkpoint->ch[1]+incr;
					checkpoint->advances++;
					return ACTION::advance;
				case 3: checkpoint->advances+=incr;
					if (iter == 0)
					{
						capo = checkpoint->ch[oldind];
						for(int i=0;i<=(t+1)/2;i++)
						{
							capo += incr;
							incr++;
							iter++;
						}
					}
					else
					{
						capo = checkpoint->ch[ind]+incr;
						iter++;
						incr++;
					}
					
					return ACTION::advance;
				default: if (capo == snaps-1)
					{
						capo = capo+2;
						ind=snaps-1;
						checkpoint->advances+=2;
						return ACTION::advance;
					}
					if (output)
						cout << " iter " << iter << " incr " << incr << "offset" << offset << endl;
					if (t == 0)
					{
						if (iter < offset)
						{
							capo = capo+1;
							checkpoint->advances++;
						}
						else
						{
							capo = capo+2;
							checkpoint->advances+=2;
						}
						if (offset == 1)
							t++;
						return ACTION::advance;
					}
					if (output)
						cout << " iter " << iter << "incr " << incr << endl;
					cout << " not implemented yet" << endl;
					return ACTION::error;
			}
		}
		else
			// takeshot for r=2
		{
			switch (snaps)
			{
				case 2: checkpoint->ch[1] = capo;
					incr++;
					// Increase the number of takeshots and the corresponding checkpoint
					checkpoint->takeshots++;
					//checkpoint->number_of_writes[1]++;
					return ACTION::takeshot;
				case 3: checkpoint->ch[ind] = capo;
					check = ind;
					cout <<" iter " << iter << " num_rep[1] " << num_rep[1] << endl;
					if (iter == num_rep[1])
					{
						iter = 0;
						t++;
						oldind = ind;
						num_rep[1]++;
						ind = 2 - num_rep[1]%2;
						incr=1;
					}
					// Increase the number of takeshots and the corresponding checkpoint
					checkpoint->takeshots++;
					//checkpoint->number_of_writes[check]++;
					return ACTION::takeshot;
				default: if (capo < snaps+2)
					{
						checkpoint->ch[ind] = capo;
						check = ind;
						if (capo == snaps+1)
						{
							oldind = checkpoint->ord_ch[snaps-1];
							ind = checkpoint->ch[checkpoint->ord_ch[snaps-1]];
							if (output)
								cout << " oldind " << oldind << " ind " << ind << endl;
							for(int k=snaps-1;k>1;k--)
							{
								checkpoint->ord_ch[k]=checkpoint->ord_ch[k-1];
								checkpoint->ch[checkpoint->ord_ch[k]] = checkpoint->ch[checkpoint->ord_ch[k-1]];
							}
							checkpoint->ord_ch[1] = oldind;
							checkpoint->ch[checkpoint->ord_ch[1]] = ind;
							incr=2;
							ind = 2;
							if (output)
							{
								cout << " ind " << ind << " incr " << incr << " iter " << iter << endl;
								for(int j=0;j<snaps;j++)
									cout << " j " << j << " ord_ch " << checkpoint->ord_ch[j] << " ch " << checkpoint->ch[checkpoint->ord_ch[j]] << " rep " << num_rep[checkpoint->ord_ch[j]] << endl;
							}
						}
						// Increase the number of takeshots and the corresponding checkpoint
						checkpoint->takeshots++;
						//checkpoint->number_of_writes[check]++;
						return ACTION::takeshot;
					}
					if (t == 0)
					{
						if (output)
							cout <<" ind " << ind << " incr " <<  incr << " iter " << iter << " offset " << offset << endl;
						if (iter == offset)
						{
							offset--;
							iter = 1;
							check = checkpoint->ord_ch[snaps-1];
							checkpoint->ch[checkpoint->ord_ch[snaps-1]] = capo;
							oldind = checkpoint->ord_ch[snaps-1];
							ind = checkpoint->ch[checkpoint->ord_ch[snaps-1]];
							if (output)
								cout << " oldind " << oldind << " ind " << ind << endl;
							for(int k=snaps-1;k>incr;k--)
							{
								checkpoint->ord_ch[k]=checkpoint->ord_ch[k-1];
								checkpoint->ch[checkpoint->ord_ch[k]] = checkpoint->ch[checkpoint->ord_ch[k-1]];
							}
							checkpoint->ord_ch[incr] = oldind;
							checkpoint->ch[checkpoint->ord_ch[incr]] = ind;
							incr++;
							ind=incr;
							if (output)
							{
								cout << " ind " << ind << " incr " << incr << " iter " << iter << endl;
								for(int j=0;j<snaps;j++)
									cout << " j " << j << " ord_ch " << checkpoint->ord_ch[j] << " ch " << checkpoint->ch[checkpoint->ord_ch[j]] << " rep " << num_rep[checkpoint->ord_ch[j]] <<  endl;
							}
						}
						else
						{
							checkpoint->ch[checkpoint->ord_ch[ind]] = capo;
							check = checkpoint->ord_ch[ind];
							iter++;
							ind++;
							if (output)
								cout << " xx ind " << ind << " incr " << incr << " iter " << iter << endl;
						}
						// Increase the number of takeshots and the corresponding checkpoint
						checkpoint->takeshots++;
						//checkpoint->number_of_writes[check]++;
						return ACTION::takeshot;
					}
			}
		}
	}
	return ACTION::terminate;  // This means that the end of Online Checkpointing for r=2 is reached and
	//	another Online Checkpointing class must be started
}

/***********************************************************************************************************************************
All routines of class Online_r3
***********************************************************************************************************************************/

Online_r3::Online_r3(int sn,Checkpoint *c) : Online(sn,c)
{
	capo=(snaps+2)*(snaps+1)/2-1;
	ch3.reserve(snaps);
	cp_fest.reserve(snaps);
	tdiff.reserve(snaps);
	tdiff_end.reserve(snaps);
	check=1;
	for(int i=0;i<snaps;i++)
	{
		tdiff[i]=i+3;
		checkpoint->ord_ch[i]=snaps-i;
		cp_fest[i]=false;
	}
	tdiff_end[0]=6;
	for(int i=1;i<snaps;i++)
	{
		tdiff_end[i]=tdiff_end[i-1]+3+i;
	}
	ch3[0]=0;
	for(int i=1;i<snaps;i++)
	{
		ch3[i]=ch3[i-1]+tdiff_end[snaps-i-1];
	}

}

Online_r3::Online_r3(Online_r3 &o) : Online(o)
{
	capo=(snaps+2)*(snaps+1)/2-1;
	ch3.reserve(snaps);
	cp_fest.reserve(snaps);
	tdiff.reserve(snaps);
	tdiff_end.reserve(snaps);
	for(int i=0;i<snaps;i++)
	{
		tdiff[i]=i+3;
		//ord_ch[i]=snaps-i;
		cp_fest[i]=false;
	}
	tdiff_end[0]=6;
	for(int i=1;i<snaps;i++)
	{
		tdiff_end[i]=tdiff_end[i-1]+3+i;
	}
	ch3[0]=0;
	for(int i=1;i<snaps;i++)
	{
		ch3[i]=ch3[i-1]+tdiff_end[snaps-i-1];
	}
}


Online_r3::~Online_r3()
{
	//delete [] cp_fest;
	//delete [] tdiff;
	//delete [] tdiff_end;
	//delete [] ch3;
}

ACTION::action Online_r3::revolve()
{
	checkpoint->commands++;
	int n=1;
	if(capo==(snaps+2)*(snaps+1)/2-1)
		// Initialisation
	{

		capo+=1;
		forward=3;
		ind_now=1;
		checkpoint->advances+=3;
		cp=0;   /* changed 26.2.10*/
		return ACTION::advance;
	}
	else
	{
		if(capo==checkpoint->ch[check])
		{
			
			if(ind_now==snaps)
				forward = 1;
			else
			{
				if(capo==ch3[ind_now]-1)
					forward=1;
			}
			capo+=forward;
			checkpoint->advances+=forward;
			return ACTION::advance;
		}
		else if(capo<=(snaps+3)*(snaps+2)*(snaps+1)/6-4)
		{
			if(cp==0 && forward==1)
				//Now we take a checkpoint and the difference between the minimal number and this number
				// equals two
			{
				cp=0;
			}
			else
			{
				cp=choose_cp(n);
				while(cp_fest[checkpoint->ord_ch[snaps-1-cp]])
				{
					cp=choose_cp(++n);
				}
			}
			checkpoint->ch[checkpoint->ord_ch[snaps-1-cp]]=capo;
			tdiff_akt();
			akt_cp();
			check=checkpoint->ord_ch[snaps-1];
			if(checkpoint->ch[check]==ch3[ind_now])
				//saves a checkpoint that cannot be overwritten
			{
				cp_fest[check]=true;
				ind_now++;
			}
			forward=3;
			// Increase the number of takeshots and the corresponding checkpoint
			checkpoint->takeshots++;
			//checkpoint->number_of_writes[check]++;
			return ACTION::takeshot;
		}
		else
		{	// end of Online Checkpointing for r=3 is reached
			return ACTION::terminate;
		}
	}

}

// Function for selection of a checkpoint that can be replaced
// important for Online-Checkpointing for r=3
int Online_r3::choose_cp(int number)
{
	int i=2;
	if(tdiff[0]==3 && number==1) return 0;
	if(tdiff[0]+tdiff[1]<=10 && number<=2) return 1;
	while(number>0)
	{
		if(tdiff[i-1]+tdiff[i]<=tdiff_end[i])
		{
			number--;
		}
		i++;
	}
	return i-1;
}

// Renews the differences between the checkpoints
// Online-Checkpointing for r=3
void Online_r3::tdiff_akt()
{
	int i,sum;
	if(cp==0)
	{
		if(forward==3) tdiff[0]=6;
		else	tdiff[0]+=1;
		return;
	}
	else
	{
		sum=tdiff[0];
		//cp[0]=3;
	}
	for(i=cp-1;i>0;i--)
	{
		sum+=tdiff[i]-tdiff[i-1];
		tdiff[i]=tdiff[i-1];
	}
	tdiff[cp]+=sum;
	tdiff[0]=3;
}

// Renews the array of the indices of checkpoints
// Online-Checkpointing for r=3
void Online_r3::akt_cp()
{
	int i;
	if(cp==0) return;
	int value=checkpoint->ord_ch[snaps-1-cp];
	for(i=cp;i>0;i--)
	{
		//c[i+1]=c[i];
		checkpoint->ord_ch[snaps-i-1]=checkpoint->ord_ch[snaps-i];
	}
	//c[0]=value;
	checkpoint->ord_ch[snaps-1]=value;
}




/*******************************************************************************************************************************************
All routines of class Arevolve
********************************************************************************************************************************************/

Arevolve::Arevolve(int sn,Checkpoint *c) : Online(sn,c)
{
	checkmax=snaps-1;
	capo=(snaps+3)*(snaps+2)*(snaps+1)/6-1;
	fine = capo+2;
	check=snaps-1;
	oldcapo=capo;
	newcapo=capo;
}

Arevolve::Arevolve(Arevolve &o) : Online(o)
{
	checkmax=snaps-1;
	fine = o.get_capo()+2;
	oldcapo=capo;
	newcapo=capo;
	check=snaps-1;
}


int Arevolve::tmin(int steps, int snaps)
{
	int reps, range, num;

	if (snaps < 1)
	{
		cout << " error occurs in tmin: snaps < 1 " << endl;
		return -1;
	}
	if (snaps > checkup)
	{
		cout << " number of snaps = " << snaps << " exceeds checkup " << endl;
		cout << " redefine 'checkup' " << endl;
		return -1;
	}
	reps = 0;
	range = 1;
	while (range < steps)
	{
		reps += 1;
		range = range*(reps + snaps)/reps;
	}
	if (reps > repsup)
	{
		cout << " number of reps = " << reps << " exceeds repsup " << endl;
		cout << " redefine 'repsup' " << endl;
		return -1;
	}
	num = reps * steps - range*reps/(snaps+1);
	return num;
}

/* ************************************************************************* */

int Arevolve::sumtmin()
{
	int p=0, i;
	//if ( (check < 1)  &&  (steps>1) )
	//    return  MAXINT;
	for ( i=0; i<snaps-1; i++ )
		p += tmin(checkpoint->ch[checkpoint->ord_ch[i+1]]-checkpoint->ch[checkpoint->ord_ch[i]],snaps-i);
	p = p + tmin(fine-1-checkpoint->ch[checkpoint->ord_ch[snaps-1]], 1) + fine-1;
	return p;
}

/* ************************************************************************* */

int Arevolve::mintmin( )
{
	int G=MAXINT, k=0, z=0, sum=0, g=0,i;


	sum=sumtmin();
	for (int j=1; j<snaps; j++)
	{
		g = z;
		if ( j-2>=0 )
		{
			g = z+tmin( checkpoint->ch[checkpoint->ord_ch[j-1]]-checkpoint->ch[checkpoint->ord_ch[j-2]], snaps-j+2 ) ;
			z=g;
		}
		if(j<snaps-1)
		{
			g += tmin( checkpoint->ch[checkpoint->ord_ch[j+1]]-checkpoint->ch[checkpoint->ord_ch[j-1]], snaps-j+1 ) ;
			for (i=j+1 ; i<=snaps-2; i++)
				g += tmin( checkpoint->ch[checkpoint->ord_ch[i+1]]-checkpoint->ch[checkpoint->ord_ch[i]], snaps-i+1 ) ;
			g+=tmin( fine-1-checkpoint->ch[checkpoint->ord_ch[snaps-1]], 2 ) ;
		}
		else
			g+=tmin( fine-1-checkpoint->ch[checkpoint->ord_ch[snaps-2]], 2 );
		if (g < G )
		{
			G = g;
			k = j;
		}
	}
	g = G + fine-1;
	if ( g < sum )
		return k;
	else
		return 0;
}

/* ************************************************************************* */
void Arevolve::akt_cp(int cp)
{
	int value =checkpoint->ord_ch[cp];

	for(int j=cp;j<snaps-1;j++)
		checkpoint->ord_ch[j]=checkpoint->ord_ch[j+1];
	checkpoint->ord_ch[snaps-1]=value;
}


ACTION::action Arevolve::revolve()
{

	oldcapo=capo;
	int shift = mintmin( );
	checkpoint->commands++;

	if ( shift==0 )
	{
		capo = oldcapo+1;
		oldfine = fine;
		//advances += capo-oldcapo;
		fine++;
		checkpoint->advances++;
		return  ACTION::advance;   //while arevolve
	}
	else
	{
		capo = oldcapo+1;
		checkpoint->ch[checkpoint->ord_ch[shift]]=capo;
		akt_cp(shift);
		check=checkpoint->ord_ch[shift];
		oldfine = fine++;
		newcapo = capo;
		checkpoint->takeshots++;
		//checkpoint->number_of_writes[check]++;
		return   ACTION::takeshot;
	}

}

/*******************************************************************************************************************************************
All routines of class Moin
********************************************************************************************************************************************/

Moin::Moin(int sn,Checkpoint *c) : Online(sn,c)
{
	capo=(snaps+3)*(snaps+2)*(snaps+1)/6-1;
	d.reserve(snaps);
	l.reserve(snaps);
	l[0]=10000;
	d[0]=false;
	for(int i=1;i<snaps;i++)
	{
		l[i]=2;
		d[i]=true;
	}
	start=true;
	start1=true;
	is_d=false;
	check=0;
}

Moin::Moin(Moin &o) : Online(o)
{
	
}

bool Moin::is_dispensable(int *index)
{
	bool dis=false;
	int ind=0;
	for(int i=snaps-1;i>0;i--)
	{
		if(d[i])
		{
			dis=true;
			if(checkpoint->ch[i]>ind)
			{
				ind=checkpoint->ch[i];
				*index = i;
			}
		}
	}
	return dis;
		
}

int Moin::get_lmin()
{
	int lmin=l[1];

	for(int i=2;i<snaps;i++)
	{
		if(l[i]<lmin)
			lmin=l[i];
	}
	return lmin;
}

void Moin::adjust_cp(int index)
{
	int level = l[index];
	int time  = checkpoint->ch[index];

	for(int i=snaps-1;i>0;i--)
	{
		if(i != index)
		{
			if(l[i]<level && checkpoint->ch[i] < time)
			{
				d[i] = true;
			}
		}
	}
}

ACTION::action Moin::revolve()
{
	int index;
	//checkpoint->print_ch(cout);
	//checkpoint->print_ord_ch(cout);
	
	//cout << "\n \n capo = " << capo;
	//cout << "\n \n snaps = " << snaps;
	checkpoint->commands++;
	if(start) 
	{
		capo++;
		start=false;
		checkpoint->advances++;
		return ACTION::advance;
	}
	if(start1)
	{
		start1=false;
		for(int i=1;i<snaps;i++)
		{
			if(checkpoint->ord_ch[i]==snaps-1)
			{
				checkpoint->ch[i] = capo;
				check=i;
				l[i]=3;
				d[i]=false;
				
			}
		}	
		forward=1;
		// Increase the number of takeshots and the corresponding checkpoint
		checkpoint->takeshots++;
		//checkpoint->number_of_writes[check]++;
		return ACTION::takeshot;
	}
	if(forward>0)
	{
		capo +=forward;
		forward=0;
		checkpoint->advances++;
		return ACTION::advance;
	}
	else
	{
		if(is_dispensable(&index))
		{
			//cout << "is_dispensable " << endl;
			checkpoint->ch[index] = capo;
			l[index] = 0;
			d[index] = false;
			index_old = index;	
			forward=1;
			check = index;
			checkpoint->takeshots++;
			return ACTION::takeshot;
		}
		else if(is_d)
		{
			//cout << "is_d=true " << endl;
			checkpoint->ch[index_old] = capo;
			check=index_old;
			lmin = get_lmin();
			l[index_old] = lmin+1;
			d[index_old]=false;
			//cout << "check = " << check << "  forward= " << lmin+1 << endl;
			adjust_cp(index_old);
			is_d=false;
			forward=1;
			checkpoint->takeshots++;
			return ACTION::takeshot;
		}
		else
		{
			lmin = get_lmin();
			//cout << "lmin = " << lmin << endl;
			forward = lmin+1;
			capo +=forward;
			is_d=true;
			forward=0;
			checkpoint->advances++;
			return ACTION::advance;
			
			//cout << "i = " << i << endl;
			
		}
	}
	cout << "\n \n Irgendwas ist falsch \n\n";
	return ACTION::terminate;	
}

/***************************************************************************************************************************************
All routines of class Offline
****************************************************************************************************************************************/



Offline::Offline(int st,int sn,Checkpoint *c) : Schedule(sn,c)
{
	//advances = 0;
	//takeshots = 0;
	//commands = 0;
	steps=st;
	check=-1;
	info=3;
	fine=steps;
	capo=0;
	online=false;
}

Offline::Offline( int sn,Checkpoint *c,Online *o,int f) : Schedule(sn,c )
{

	checkpoint->ch[0]=0;
	online=true;
	check=o->get_check();

	capo=o->get_capo();
	turn=0;
	num_ch.reserve(snaps);
	ind = 0;
	for(int i=0;i<snaps;i++)
	{
		num_ch[i] = 0;
		for(int j=0;j<snaps;j++)
		{
			if (checkpoint->ch[j] < checkpoint->ch[i])
				num_ch[i]++;
		}
		if (o->get_output())
			cout << " i " << i << " num_ch " << num_ch[i] << " ch " << checkpoint->ch[i] << endl;
		/*for(int k=0;k<snaps;k++)
		{
			for(int j=0;j<snaps;j++)
				if (num_ch[j] == k)
					checkpoint->ord_ch[k] = j;  
			//if (o->get_output())
				printf(" i %d ord_ch %d ch %d\n",k,checkpoint->ord_ch[k],checkpoint->ch[k]);
		}*/
	}
	for(int i=0;i<snaps;i++)
	{
		for(int j=0;j<snaps;j++)
			if (num_ch[j] == i)
				checkpoint->ord_ch[i] = j; 
		if (o->get_output())
			printf(" i %d ord_ch %d ch %d\n",i,checkpoint->ord_ch[i],checkpoint->ch[i]);
	}
	checkpoint->advances = f-1;
	info=3;
	//takeshots = o->get_shots();
	//commands = o->get_commands();
	oldsnaps=snaps;
}

Offline::Offline( Schedule *o) : Schedule(o->get_snaps() )
{}

Offline::Offline( Offline &o) : Schedule(o.get_snaps(),o.get_CP())
{
	//advances = o.get_advances();
	//takeshots = o.get_shots();
	//commands = o.get_commands();
	steps=o.get_steps();
	check=o.get_check();
	info=3;
	fine=o.get_steps();
	capo=o.get_capo();
	online=o.get_online();
	num_ch.reserve( snaps);
	for(int i=0;i<snaps;i++)
	{
		num_ch[i]=o.get_num_ch(i);
	}
	oldsnaps=snaps;

}

ACTION::action Offline::revolve()
{
	checkpoint->commands++;
	if ((check < -1) || (capo > fine))
		return ACTION::error;
	if ((check == -1) && (capo < fine))
	{
		if (check == -1)
			turn = 0;   /* initialization of turn counter */
		checkpoint->ch[0] = capo-1;
	}
	switch (fine-capo)
	{
		case 0:   /* reduce capo to previous checkpoint, unless done  */
			if (check == -1 || capo==checkpoint->ch[0] )
			{
				if (info > 0)
				{
					cout << "\n advances: " << setw(5) << checkpoint->advances;
					cout << "\n takeshots: " << setw(5) << checkpoint->takeshots;
					cout << "\n commands: " << setw(5) << checkpoint->commands << endl;
				}
				return ACTION::terminate;
			}
			else
			{
				if(online)
				{
					int ind = 0;
					for(int i=0;i<snaps;i++)
					{
						if ((checkpoint->ch[i] > checkpoint->ch[ind]) && (checkpoint->ch[i] < capo))
							ind = i;
					}
					check = ind;
				}
				capo = checkpoint->ch[check];
				oldfine = fine;
				checkpoint->number_of_reads[check]++;
				return ACTION::restore;
			}
		case 1:  /* (possibly first) combined forward/reverse step */
			fine -= 1;
			if (check >= 0 && checkpoint->ch[check] == capo)
				check -= 1;
			if (turn == 0)
			{
				turn = 1;
				oldfine = fine;
				return ACTION::firsturn;
			}
			else
			{
				oldfine = fine;
				return ACTION::youturn;
			}
		default:
			if (check==-1)
				// Initialisation
			{
				checkpoint->ch[0]=0;
				check=0;
				oldsnaps = snaps;
				if (snaps > checkup)
				{
					info = 14;
					return ACTION::error;
				}
				if (info > 0)
				{
					int num = numforw(fine-capo,snaps);
					if (num == -1)
					{
						info = 12;
						return ACTION::error;
					}
					cout << " prediction of needed forward steps: " << setw(8) << num << " => " << endl;
					cout << " slowdown factor: " << setiosflags(ios::fixed) << setprecision(4) << ((double) num)/(fine-capo)<< endl << endl;
				}
				oldfine = fine;
				//last_action=takeshot;
				checkpoint->number_of_writes[check]++;
				checkpoint->takeshots++;
				return ACTION::takeshot;
			}
			if (checkpoint->ch[check]!=capo)
				// takeshot
			{
				if (online)					
					check=checkpoint->ord_ch[num_ch[check]+1];
				else
					check++;
				if (check >= checkup)
				{
					info = 10;
					return ACTION::error;
				}
				if (check+1 > snaps)
				{
					info = 11;
					return ACTION::error;
				}
				checkpoint->ch[check] = capo;
				checkpoint->takeshots++;
				oldfine = fine;
				//last_action=takeshot;
				checkpoint->number_of_writes[check]++;
				return ACTION::takeshot;
			}
			else
				// advance
			{
				if ((oldfine < fine) && (snaps == check+1))
				{
					info = 13;
					return ACTION::error;
				}
				int oldcapo = capo;
				int ds;
				if (online)
					ds = snaps - num_ch[check];
				else
					ds = snaps - check;
				if (ds < 1)
				{
					info = 11;
					return ACTION::error;
				}
				int reps = 0;
				int range = 1;
				while (range < fine - capo)
				{
					reps += 1;
					range = range*(reps + ds)/reps;
				}
				if (reps > repsup)
				{
					info = 15;
					return ACTION::error;
				}
				if (snaps != oldsnaps)
				{
					if (snaps > checkup)
					{
						info = 14;
						return ACTION::error;
					}
				}
				int bino1 = range*reps/(ds+reps);
				int bino2 = (ds > 1) ? bino1*ds/(ds+reps-1) : 1;
				int bino3;
				if (ds == 1)
					bino3 = 0;
				else
					bino3 = (ds > 2) ? bino2*(ds-1)/(ds+reps-2) : 1;
				int bino4 = bino2*(reps-1)/ds;
				int bino5;
				if (ds < 3)
					bino5 = 0;
				else
					bino5 = (ds > 3) ? bino3*(ds-2)/reps : 1;

				if (fine-capo <= bino1 + bino3)
					capo = capo+bino4;
				else
				{
					if (fine-capo >= range - bino5)
						capo = capo + bino1;
					else
						capo = fine-bino2-bino3;
				}
				if (capo == oldcapo)
					capo = oldcapo+1;
				checkpoint->advances += capo - oldcapo;
				oldfine = fine;
				//last_action=advance;
				return ACTION::advance;
			}
	}
}


// All routines of class Revolve

Revolve::Revolve(int st,int sn)
{
	
	capo=0;
	checkpoint = new Checkpoint(sn);
	f=new Offline(st,sn,checkpoint);
	online=false;
	steps=st;
	snaps=sn;
	check=-1;
	info = 1;
	multi=false;
	where.reserve(snaps);
	for(int i=0;i<snaps;i++)
		where[i] = true;
	checkpoint->advances=0;
	checkpoint->takeshots=0;
	checkpoint->commands=0;
}

Revolve::Revolve(int st,int sn,int sn_ram)
{
	vector <int> v;
	int num=0,mid;
	
	checkpoint = new Checkpoint(sn);
	f=new Offline(st,sn,checkpoint);
	online=false;
	steps=st;
	snaps=sn;
	check=-1;
	info = 1;
	multi=true;
	where.reserve(snaps);
	indizes_ram.reserve(snaps);
	indizes_rom.reserve(snaps);	
	
	v = get_write_and_read_counts();
	sort(v.begin(),v.end());
	mid=v[snaps-sn_ram];
	//cout << mid << endl;
	for(int i=snaps-1;i>=0;i--)
	{
		if(v[i]>=mid && num<sn_ram)
		{
			where[i]=true;
			num++;
		}
		else
		{
			where[i]=false;
		}
	}
	int j=0,k=0;
	for(int i=0;i<snaps;i++)
	{
		if(where[i])
			indizes_ram[i]=j++;
		else
			indizes_rom[i]=k++;
	} 		
	checkpoint->advances=0;
	checkpoint->takeshots=0;
	checkpoint->commands=0;
}

Revolve::Revolve(int sn)
{
	checkpoint = new Checkpoint(sn);
	f=new Online_r2(sn,checkpoint);
	where.reserve(sn);
	online=true;
	snaps=sn;
	//info=inf;
	check=-1;
	info = 1;
	r=2;
	checkpoint->advances=0;
	checkpoint->takeshots=0;
	checkpoint->commands=0;
}

ACTION::action Revolve::revolve(int* check,int* capo,int* fine,int snaps,int* info,bool *where_to_put)
{
	ACTION::action whatodo;
	whatodo=f->revolve();
	if(online && whatodo==ACTION::terminate && r==2)
	{
		f = new Online_r3(snaps,checkpoint);
		whatodo=f->revolve();
		r++;
	}
	if(online && whatodo==ACTION::terminate && r==3)
	{
		f = new Moin(snaps,checkpoint);
		whatodo=f->revolve();
		r++;
	}
	*check=f->get_check();
	*capo=f->get_capo();
	*fine=f->get_fine();
	//*info=f->get_info();
	if(*check==-1) return whatodo;
	*where_to_put=where[*check];
	return whatodo;

}

ACTION::action Revolve::revolve(int* check,int* capo,int* fine,int snaps,int* info)
{
	ACTION::action whatodo;
	whatodo=f->revolve();
	if(online && whatodo==ACTION::terminate && r==2)
	{
		delete f;
		f = new Online_r3(snaps,checkpoint);
		whatodo=f->revolve();
		r++;
	}
	if(online && whatodo==ACTION::terminate && r==3)
	{
		delete f;
		f = new Moin(snaps,checkpoint);
		whatodo=f->revolve();
		r++;
	}
	*check=f->get_check();
	*capo=f->get_capo();
	*fine=f->get_fine();
	//*info=f->get_info();
	return whatodo;
}

ACTION::action Revolve::revolve()
{
	ACTION::action whatodo;
	oldcapo = capo;
	whatodo=f->revolve();
	if(online && whatodo==ACTION::terminate && r==2)
	{
		delete f;
		f = new Online_r3(snaps,checkpoint);
		whatodo=f->revolve();
		r++;
	}
	if(online && whatodo==ACTION::terminate && r==3)
	{
		delete f;
		f = new Moin(snaps,checkpoint);
		whatodo=f->revolve();
		r++;
	}
	check=f->get_check();
	capo=f->get_capo();
	fine=f->get_fine();
	info=f->get_info();
	if(check<=-1) return whatodo;
	if(!online) where_to_put=where[check];
	return whatodo;
}




void Revolve::turn(int final)
{
	if(online)
	{
		fine=final;
		capo=final-1;
		Online *g = new Online((Online &) *f);
		delete f;
		f=new Offline(snaps,checkpoint,g,final);
		delete g;
		//f=new Offline(snaps,checkpoint,(Online*)f,final);
		f->set_fine(final);
		f->set_capo(final-1);
		online=false;
	}
}

double Revolve::expense(int steps, int snaps)
{
	double ratio;

	if (snaps < 1)
	{
		cout << " error occurs in expense: snaps < 0 " << endl;
		return -1;
	}
	if (steps < 1)
	{
		cout <<" error occurs in expense: steps < 0 " << endl;
		return -1;
	}
	ratio = ((double) numforw(steps,snaps));
	if (ratio == -1)
		return -1;
	ratio = ratio/steps;
	return ratio;
}

/* ************************************************************************* */

int Revolve::maxrange(int ss, int tt)
{
	int i, ires;
	double res = 1.0;

	if ((tt<0) || (ss<0))
	{
		cout << " error in MAXRANGE: negative parameter ";
		return -1;
	}
	for (i=1; i<= tt; i++)
	{
		res *= (ss + i);
		res /= i;
		if (res > MAXINT)
		{
			ires=MAXINT;
			cout << " warning from MAXRANGE: returned maximal integer "<< ires << endl;
			return ires;
		}
	}
	ires = (int) res;
	return ires;
}

/* ************************************************************************* */

int Revolve::adjust(int steps)
{
	int snaps, s, reps;

	snaps = 1;
	reps = 1;
	s = 0;
	while ( maxrange(snaps+s, reps+s) > steps )
		s--;
	while ( maxrange(snaps+s, reps+s) < steps )
		s++;
	snaps += s;
	reps += s ;
	s = -1;
	while ( maxrange(snaps,reps) >= steps )
	{
		if (snaps > reps)
		{
			snaps -= 1;
			s = 0;
		}
		else
		{
			reps -= 1;
			s = 1;
		}
	}
	if ( s == 0 )
		snaps += 1 ;
	if ( s == 1 )
		reps += 1;
	return snaps;
}

int Revolve::get_r(int steps,int snaps)
{
	int reps, range, num;

	if (snaps < 1)
	{
		cout << " error occurs in tmin: snaps < 1 " << endl;
		return -1;
	}
	if (snaps > checkup)
	{
		cout << " number of snaps = " << snaps << " exceeds checkup " << endl;
		cout << " redefine 'checkup' " << endl;
		return -1;
	}
	reps = 0;
	range = 1;
	while (range < steps)
	{
		reps += 1;
		range = range*(reps + snaps)/reps;
	}
	if (reps > repsup)
	{
		cout << " number of reps = " << reps << " exceeds repsup " << endl;
		cout << " redefine 'repsup' " << endl;
		return -1;
	}
	return reps;
}

int Revolve::get_r()
{
	int reps, range, num;

	if (snaps < 1)
	{
		cout << " error occurs in tmin: snaps < 1 " << endl;
		return -1;
	}
	if (snaps > checkup)
	{
		cout << " number of snaps = " << snaps << " exceeds checkup " << endl;
		cout << " redefine 'checkup' " << endl;
		return -1;
	}
	reps = 0;
	range = 1;
	while (range < steps)
	{
		reps += 1;
		range = range*(reps + snaps)/reps;
	}
	if (reps > repsup)
	{
		cout << " number of reps = " << reps << " exceeds repsup " << endl;
		cout << " redefine 'repsup' " << endl;
		return -1;
	}
	return reps;
}



vector <int> Revolve::get_write_and_read_counts()
{
	vector <int> num(snaps);
	
	for(int i=0;i<snaps;i++)
		num[i]=get_number_of_writes_i( steps,snaps,i) + get_number_of_reads_i(steps,snaps,i);
	
	return num;
}

int cal(int l,int c,int i)
{
	if(i==0) return 0;
	if(l>(1+i)*c-0.5*(i-1)*i+1) return i;
	return (int) floor(0.5*(1+2*c)-sqrt(pow(0.5*(1+2*c),2)+2*i+4-2*l))-1;
}







int Revolve::get_number_of_writes_i(int l, int c,int i)
{
	if (i==0) return 1;
	if(l <= 1+i) return 0;
	else if(l <= 2*c+i) return 1;
	else if(l <= (1+i)*c-0.5*(i-1)*i+1) return (int) floor(0.5*(1+2*c)-sqrt(pow(0.5*(1+2*c),2)+2*i+4-2*l));
	else if(l <=c*c+2.*c+i) return i+1;
	else
	{
		double l_0=c*c+2.*c+1.;
		double a=27.*c*(c*c-1.)+162.*(l_0-l);
		int k;

		if (a==0)	
			k=c-1;
		else
			k = (int) floor(c-pow(2./(a+sqrt(a*a-108.)),1./3.)-1./3.*pow(0.5*(a+sqrt(a*a-108.)),1./3.));
		
		double l_k = 1./6.*k*k*k-c/2.*k*k+1./6.*(3.*c*c-1.)*k+l_0;
		
		if(i<=k)
			return (int) (1./2.*i*i+3./2.*i+1.);
		else    
		{
			int w_i_k= (int) (i*k+i+1.- 1./2.*k*(k-1.));
			return w_i_k+cal(l-(int)l_k+2*(c-k)+1,c-k,i-k);
		}
	}
}


	
	
int Revolve::get_number_of_reads_i(int l, int c,int i)
{
	if(l <= i+1) return 0;
	else if (l <= 2*c-i) return 1;
	else if (l <= 2*c+1) return 2;
	else if (l <= c*c/2.+3.*c/2.+1) return get_number_of_writes_i(l,c,i)+1;
	else if (l <= c*c+2*c+1)	
	{	
		double a = 0.5*(4.*i-2.*c+7.);
		double b = pow(c-2.*i-3.,2.)+c+3.;
		if(l >= c*c+2*c+1-c*i+0.5*(i*i-i))
			return (int) floor(a+sqrt(a*a-b+2.*(l-0.5*c*c-1.5*c-1)));
		else
			return i+2;
	}
	else return get_number_of_writes_i(l,c,i)+i+2; 
}



const double e = 2.7182818;

using namespace std;


double func_U(double t)
{
	return 2.*(pow(e,3.*t)-pow(e,3))/(pow(e,3.*t/2.)*(2.+pow(e,3)));
}

void func(double X[2],double t, double F[2])
{
	F[0] = 0.5*X[0]+ func_U(t);
	F[1] = X[0]*X[0]+0.5*(func_U(t)*func_U(t));
}

void func_lambda(double L[2], double X[2], double F[2])
{
	F[0] = -0.5*L[0]-2.*X[0]*L[1];
	F[1] = 0.;
}

void func_adj(double BF[2], double X[2], double BX[2])
{
	BX[0] = 0.5*BF[0]+2.*X[0]*BF[1];
	BX[1] = 0.;
}

void opt_sol(double Y[2],double t)
{
	Y[0] = (2.*pow(e,3.*t)+pow(e,3))/(pow(e,3.*t/2.)*(2.+pow(e,3)));
	Y[1] = (2.*pow(e,3.*t)-pow(e,6.-3.*t)-2.+pow(e,6))/(pow(2.+pow(e,3),2));
}

void opt_lambda(double L[2],double t)
{
	L[0] = (2.*pow(e,3-t)-2.*pow(e,2.*t))/(pow(e,t/2.)*(2+pow(e,3)));
	L[1] = 1.;
}

void advance(double F[2],double F_H[2],double t,double h)
{
	double k0[2],k1[2],G[2];

	func(F_H,t,k0);
	G[0] = F_H[0] + h/2.*k0[0];
	G[1] = F_H[1] + h/2.*k0[1];
	func(G,t+h/2.,k1);
	F[0] = F_H[0] + h*k1[0];
	F[1] = F_H[1] + h*k1[1];
}

void store(double F_H[2], double **F_C,double t,int i)
{
	F_C[0][i] = F_H[0]; 
	F_C[1][i] = F_H[1];
	F_C[2][i] = t;	
}

void restore(double F_H[2], double **F_C,double *t,int i)
{
	F_H[0] = F_C[0][i]; 
	F_H[1] = F_C[1][i];
	*t = F_C[2][i];
}


void adjoint(double L_H[2],double F_H[2],double L[2],double t,double h)
{
	double k0[2],k1[2],G[2],BH[2],Bk0[2],Bk1[2],BG[2];

	func(F_H,t,k0);
	G[0] = F_H[0] + h/2.*k0[0];
	G[1] = F_H[1] + h/2.*k0[1];
	func(G,t+h/2.,k1);
	L[0] = L_H[0];
	L[1] = L_H[1];
	Bk1[0] = h*L_H[0];
	Bk1[1] = h*L_H[1];
	func_adj(Bk1,G,BG);
	L[0] += BG[0];
	L[1] += BG[1];
	Bk0[0] = h/2.*BG[0];
	Bk0[1] = h/2.*BG[1];
	func_adj(Bk0,F_H,BH);
	L[0] += BH[0];
	L[1] += BH[1];
}

int main(int argc, char *argv[])
{
	// Pointer on class Revolve because we do not know which checkpoint routine will be used
	Revolve *r;
	int online;

	// These variables merit exact and approximate solution 
	double F[2],L[2],F_opt[2],L_opt[2];
	double t,h,F_H[2],L_H[2],F_final[2];
	double **F_Check;

	cout << "**************************************************************************" << endl;
	cout << "*              Solution of the optimal control problem                   *" << endl;
	cout << "*                                                                        *" << endl;
	cout << "*                     J(y) = y_2(1) -> min                               *" << endl;
	cout << "*           s.t.   dy_1/dt = 0.5*y_1(t) + u(t),            y_1(0)=1      *" << endl;
	cout << "*                  dy_2/dt = y_1(t)^2 + 0.5*u(t)^2         y_2(0)=0      *" << endl;
	cout << "*                                                                        *" << endl;
	cout << "*                  the adjoints equations fulfill                        *" << endl;
	cout << "*                                                                        *" << endl;
	cout << "*         dl_1/dt = -0.5*l_1(t) - 2*y_1(t)*l_2(t)          l_1(1)=0      *" << endl;
	cout << "*         dl_2/dt = 0                                      l_2(1)=1      *" << endl;
	cout << "*                                                                        *" << endl;
	cout << "*   with Revolve for Online and (Multi-Stage) Offline Checkpointing      *" << endl;
	cout << "*                                                                        *" << endl;
	cout << "**************************************************************************" << endl;
		
	cout << "**************************************************************************" << endl;
	cout << "*        The solution of the optimal control problem above is            *" << endl;
	cout << "*                                                                        *" << endl;
	cout << "*        y_1*(t) = (2*e^(3t)+e^3)/(e^(3t/2)*(2+e^3))                     *" << endl;
	cout << "*        y_2*(t) = (2*e^(3t)-e^(6-3t)-2+e^6)/((2+e^3)^2)                 *" << endl;
	cout << "*          u*(t) = (2*e^(3t)-e^3)/(e^(3t/2)*(2+e^3))                     *" << endl;
	cout << "*        l_1*(t) = (2*e^(3-t)-2*e^(2t))/(e^(t/2)*(2+e^3))                *" << endl;
	cout << "*        l_2*(t) = 1                                                     *" << endl;
	cout << "*                                                                        *" << endl;
	cout << "**************************************************************************" << endl;

	cout << "\n \n Using Binomial Offline Checkpointing for the approximate solution: \n \n" ;
	
	
	//int check, capo, fine, steps, snaps,oldcapo;
	int info,snaps,steps;
	enum ACTION::action whatodo;
	//capo = 0;

	cout << endl << "STEPS    -> number of time steps to perform" << endl;
	cout << "SNAPS    -> number of checkpoints" << endl;
	cout << "INFO = 1 -> calculate only approximate solution" << endl;
	cout << "INFO = 2 -> calculate approximate solution + takeshots" << endl;
	cout << "INFO = 3 -> calculate approximate solution + all information" << endl << endl;
	cout << " ENTER:   STEPS, SNAPS, INFO \n";
	cin >> steps >> snaps >> info;
	
	// Constructor for Offline Checkpointing without Multi-Stage
	r=new Revolve(steps,snaps);
	r->set_info(info);
	h = 1./steps;
	t = 0.;
	F[0] = 1.;
	F[1] = 0.;
	
	F_Check = new double *[3];
	for (int i=0;i<3;i++)
	{
		F_Check[i] = new double [snaps];
	}
	
	do
	{
		whatodo = r->revolve();
		if (whatodo == ACTION::takeshot)
		{
			store(F,F_Check,t,r->getcheck());
			if(info > 1)
				cout << " takeshot at " << setw(6) << r->getcapo() << " in CP " << r->getcheck() << endl;
			
		}
		if (whatodo == ACTION::advance) 
		{
			for(int j=r->getoldcapo();j<r->getcapo();j++)
			{
				F_H[0] = F[0];
				F_H[1] = F[1];
				advance(F,F_H,t,h);
				t += h;		
			}
			if(info > 2)
				cout << " advance to " << setw(7) << r->getcapo() << endl;
		}	
		if (whatodo == ACTION::firsturn)
		{
			F_H[0] = F[0];
			F_H[1] = F[1];
			advance(F_final,F_H,t,h);
			L[0] = 0.;
			L[1] = 1.;
			t = 1.-h;
			L_H[0] = L[0];
			L_H[1] = L[1];
			adjoint(L_H,F_H,L,t,h);	
			if(info > 2)
				cout << " firsturn at " << setw(6) << r->getcapo() << endl;
		}
		if (whatodo == ACTION::youturn) 
		{
			L_H[0] = L[0];
			L_H[1] = L[1];
	
			adjoint(L_H,F,L,t,h);
			t = t - h;
			if(info > 2)
				cout << " youturn at " << setw(7) << r->getcapo() << endl;	
		}
		if (whatodo == ACTION::restore) 
		{
			restore(F,F_Check,&t,r->getcheck());
			if(info > 2)
				cout << " restore at " << setw(7) << r->getcapo() << " in CP " << r->getcheck() << endl;
		}
		if (whatodo == ACTION::error)
		{
			cout << " irregular termination of revolve \n";
			switch (r->getinfo())
			{
				case 10:
					cout << " number of checkpoints stored exceeds checkup, \n";
					cout << " increase constant 'checkup' and recompile \n";
					abort();
				case 11:
					cout << " number of checkpoints stored = " << r->getcheck()+1 << " exceeds snaps = " << snaps << endl;
					cout << " ensure 'snaps' > 0 and increase initial 'fine' \n";
					abort();
				case 12:
					cout << " error occurs in numforw \n";
					abort();
				case 13:
					cout << " enhancement of 'fine', 'snaps' checkpoints stored, \n";
					cout << " increase 'snaps'\n";
					abort();
				case 14:
					cout << " number of snaps exceeds snapsup, ";
					cout << " increase constant 'snapsup' and recompile \n";
					abort();
				case 15:
					cout << " number of reps exceeds repsup, ";
					cout << " increase constant 'repsup' and recompile \n";
					abort();
			}
		}
	}
	while ((whatodo != ACTION::terminate) && (whatodo != ACTION::error));
	delete r;
	for (int i=0;i<3;i++)
	{
		delete [] F_Check[i];
	}
	delete [] F_Check;
	
	opt_sol(F_opt,1.);
	opt_lambda(L_opt,0.);
	cout << "\n\n";
	cout << "y_1*(1)  = " << setiosflags(ios::fixed) << setprecision(7) << F_opt[0] << "  ";
	cout << "y_2*(1)  = " << setiosflags(ios::fixed) << setprecision(7) << F_opt[1] << endl;	
	cout << "y_1 (1)  = " << setiosflags(ios::fixed) << setprecision(7) << F_final[0] << "  ";
	cout << "y_2 (1)  = " << setiosflags(ios::fixed) << setprecision(7) << F_final[1] << endl;	
	cout << "\n\n";
	cout << "l_1*(0)  = " << setiosflags(ios::fixed) << setprecision(7) << L_opt[0] << "  ";
	cout << "l_2*(0)  = " << setiosflags(ios::fixed) << setprecision(7) << L_opt[1] << endl;		
	cout << "l_1 (0)  = " << setiosflags(ios::fixed) << setprecision(7) << L[0]     << "  ";
	cout << "l_2 (0)  = " << setiosflags(ios::fixed) << setprecision(7) << L[1] << endl;	
}
 
