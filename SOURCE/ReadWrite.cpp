//Read/Write module. Built by Julian Hershey, 2012. Use as you wish. Beware of human-made errors!

//The way this works is it includes agent.h, world.h, and glview.h, and is included by glview.cpp.
//I was unable to have this between world.h and glview.h. If you can find a better way to use this,
//please do so and let me know @ julian.hershey@gmail.com

//Currently, GLView has to create an instance of this class whenever saving or loading is needed (see GLView::menu)
//once that is done, the world and other data must be fed to the functions of ReadWrite in order to fully save all data
//It's not pretty, but it works

//Data can be saved in any file format, as the data is put into text form. I tried to emulate XML, but I did not
//strictly follow those rules. There must be a space between the equals sign and the data being loaded, or there
//will be failures. I've made use of a mode var to better control when certain objects and data should be expected.

//For loading agents: I've used <agent> and </agent> tags to outline individual agents. Upon loading, a fake agent
//is created, all attributes which have data to be retrieved are set, and the </agent> tag signals the copy of the
//fake agent's variables into a real agent placed in the world array.

//IN THE FILES: Order does not matter, as each line is read individually from the others. HOWEVER, cell data MUST
//be contained inside <cell>, and agent data MUST be included in its own <agent>. If something goes wrong and 
//two lines modify the same attribute, the latter one will be used.

//VERSION CHECKING: As of now, the system seems to deal with missing data quite harmlessly;
//in the case of agent vars missing, random init data values are assigned; in the case of
//world data, nothing can break down because those values are set by the program. Cells may break since it's more 
//complex, so beware. Even too much data (eg some old data that is no longer used by the program) isn't a
//big issue; simply remove the already removed variable and the line check for it.

#include "ReadWrite.h"

using namespace std;

ReadWrite::ReadWrite()
{
	ourfile= "WORLD.SAV";
}

void ReadWrite::loadSettings(const char *filename)
{
	char line[64], *pos;
	char var[16];
	char dataval[16];

	//if no filename given, use default
	if(filename=="" || filename==0){
		filename= "settings.txt";
		printf("No filename given. Loading default settings.txt instead.\n");
	}

	//open the file
	FILE* sf = fopen(filename, "r");

	if(sf){
		printf("file exists! loading");
		while(!feof(sf)){
			fgets(line, sizeof(line), sf);
			pos= strtok(line,"\n");
			sscanf(line, "%s%s", var, dataval);
		
		}
	}
}


void ReadWrite::saveAgent(Agent *a, FILE *file)
{
	//NOTE: this method REQUIRES "file" to be opened and closed outside
	//flags: <a></a>= agent, <y>= eye, <e>= ear, <b>=brain, <n>= conn, <x>= box
	fprintf(file, "<a>\n"); //signals the writing of a new agent
	//variables: changing values
	fprintf(file, "posx= %f\nposy= %f\n", a->pos.x, a->pos.y);
	fprintf(file, "angle= %f\n", a->angle);
	fprintf(file, "age= %i\n", a->age);
	fprintf(file, "gen= %i\n", a->gencount);
	fprintf(file, "hybrid= %i\n", (int) a->hybrid);
	fprintf(file, "health= %f\n", a->health);
	fprintf(file, "exhaustion= %f\n", a->exhaustion);
	fprintf(file, "repcounter= %f\n", a->repcounter);
	fprintf(file, "carcasscount= %i\n", a->carcasscount);
	fprintf(file, "freshkill= %i\n", a->freshkill);
	fprintf(file, "spike= %f\n", a->spikeLength);
	fprintf(file, "jump= %f\n", a->jump);
	fprintf(file, "dhealth= %f\n", a->dhealth);

	//traits: fixed values
	fprintf(file, "species= %i\n", a->species);
	fprintf(file, "kinrange= %i\n", a->kinrange);
	fprintf(file, "radius= %f\n", a->radius);
	fprintf(file, "gene_red= %f\ngene_gre= %f\ngene_blu= %f\n", a->gene_red, a->gene_gre, a->gene_blu);
	fprintf(file, "chamovid= %f\n", a->chamovid);
	fprintf(file, "sexprojectbias= %f\n", a->sexprojectbias);
	fprintf(file, "herb= %f\n", a->stomach[Stomach::PLANT]);
	fprintf(file, "carn= %f\n", a->stomach[Stomach::MEAT]);
	fprintf(file, "frug= %f\n", a->stomach[Stomach::FRUIT]);
	fprintf(file, "numbabies= %i\n", a->numbabies);
	fprintf(file, "metab= %f\n", a->metabolism);
	fprintf(file, "temppref= %f\n", a->temperature_preference);
	fprintf(file, "lungs= %f\n", a->lungs);
	fprintf(file, "brain_mutchance= %f\n", a->brain_mutation_chance);
	fprintf(file, "brain_mutsize= %f\n", a->brain_mutation_size);
	fprintf(file, "gene_mutchance= %f\n", a->gene_mutation_chance);
	fprintf(file, "gene_mutsize= %f\n", a->gene_mutation_size);
	fprintf(file, "parentid= %i\n", a->parentid);
	fprintf(file, "strength= %f\n", a->strength);
	fprintf(file, "cl1= %f\ncl2= %f\n", a->clockf1, a->clockf2);
	fprintf(file, "smellmod= %f\n", a->smell_mod);
	fprintf(file, "hearmod= %f\n", a->hear_mod);
	fprintf(file, "bloodmod= %f\n", a->blood_mod);
	fprintf(file, "eyemod_agent= %f\n", a->eye_see_agent_mod);
	fprintf(file, "eyemod_cell= %f\n", a->eye_see_cell_mod);
//		fprintf(file, "eyecellmod= %f\n", a->eye_see_cell_mod);
	for(int q=0;q<a->eyedir.size();q++) {
		fprintf(file, "<y>\n");
		fprintf(file, "eye#= %i\n", q);
		fprintf(file, "eyedir= %f\n", a->eyedir[q]);
		fprintf(file, "eyefov= %f\n", a->eyefov[q]);
		fprintf(file, "</y>\n");
	}
	for(int q=0;q<NUMEARS;q++) {
		fprintf(file, "<e>\n");
		fprintf(file, "ear#= %i\n", q);
		fprintf(file, "eardir= %f\n", a->eardir[q]);
		fprintf(file, "hearlow= %f\n", a->hearlow[q]);
		fprintf(file, "hearhigh= %f\n", a->hearhigh[q]);
		fprintf(file, "</e>\n");
	}
	//Note: Stats aren't saved
//	fprintf(file, "indicator= %f\n", a->indicator);
//	fprintf(file, "ir= %f\nig= %f\nib= %f\n", a->ir, a->ig, a->ib);
	fprintf(file, "<b>\n"); //signals the writing of the brain (more for organization than proper loading)
	fprintf(file, "boxes= %i\n", a->brain.boxes.size());
	fprintf(file, "conns= %i\n", a->brain.conns.size());

	for(int c=0;c<a->brain.conns.size();c++){
		fprintf(file, "<n>\n"); //signals the writing of a specific numbered conn
		fprintf(file, "conn#= %i\n", c);
		fprintf(file, "type= %i\n", a->brain.conns[c].type);
		fprintf(file, "w= %f\n", a->brain.conns[c].w);
		fprintf(file, "sid= %i\n", a->brain.conns[c].sid);
		fprintf(file, "tid= %i\n", a->brain.conns[c].tid);
		fprintf(file, "seed= %i\n", a->brain.conns[c].seed);
		fprintf(file, "</n>\n"); //end of conn
	}

	for(int b=0;b<a->brain.boxes.size();b++){
		fprintf(file, "<x>\n"); //signals the writing of a specific numbered box
		fprintf(file, "box#= %i\n", b);
		fprintf(file, "kp= %f\n", a->brain.boxes[b].kp);
		fprintf(file, "globalw= %f\n", a->brain.boxes[b].gw);
		fprintf(file, "bias= %f\n", a->brain.boxes[b].bias);
		fprintf(file, "seed= %i\n", a->brain.boxes[b].seed);
		fprintf(file, "dead= %i\n", (int)a->brain.boxes[b].dead);
		if(!a->isDead()) {
			fprintf(file, "target= %f\n", a->brain.boxes[b].target);
			fprintf(file, "out= %f\n", a->brain.boxes[b].out);
			fprintf(file, "oldout= %f\n", a->brain.boxes[b].oldout);
		}
		fprintf(file, "</x>\n"); //end of box
	}
	fprintf(file, "</b>\n"); //end of brain
	fprintf(file, "</a>\n"); //end of agent
}

void ReadWrite::loadAgents(World *world, FILE *file, float fileversion, bool loadexact)
{
	//NOTE: this method REQUIRES "file" to be opened and closed outside
	//loadexact is flag for loading agent EXACTLY is same pos, same health, exhaustion, etc, if set to false we give it random spawn settings for non-genes
	char address[32];
	char line[64], *pos;
	char var[32];
	char dataval[16];
	int mode= ReadWriteMode::READY;

	Agent xa(
		world->BRAINBOXES,
		world->BRAINCONNS,
		world->SPAWN_MIRROR_EYES,
		world->OVERRIDE_KINRANGE,
		world->MEANRADIUS,
		world->REP_PER_BABY,
		world->DEFAULT_BRAIN_MUTCHANCE,
		world->DEFAULT_BRAIN_MUTSIZE,
		world->DEFAULT_GENE_MUTCHANCE,
		world->DEFAULT_GENE_MUTSIZE
	); //Agent::Agent //mock agent. gets moved and deleted after loading
	bool t2= false; //triggers for keeping track of where exactly we are

	int eyenum= -1; //temporary index holders
	int earnum= -1;
	int boxnum= -1;
	int connnum= -1;
	int i; //integer buffer
	float f; //float buffer


	while(!feof(file)){
		fgets(line, sizeof(line), file);
		pos= strtok(line,"\n");
		sscanf(line, "%s%s", var, dataval);

		if(mode==ReadWriteMode::READY) {
			if(strcmp(var, "<a>")==0){
				mode = ReadWriteMode::AGENT;
			}
		}
		
		if(mode==ReadWriteMode::AGENT){
			if(strcmp(var, "</a>")==0){
				//end agent tag is checked for, and when found, copies agent xa to the world
				if(loadexact) world->addAgent(xa);
				else world->loadedagent= xa; //if we are loading a single agent, push it to buffer
			}else if(strcmp(var, "posx=")==0 && loadexact){
				sscanf(dataval, "%f", &f);
				xa.pos.x= f;
				xa.dpos.x= f;
			}else if(strcmp(var, "posy=")==0 && loadexact){
				sscanf(dataval, "%f", &f);
				xa.pos.y= f;
				xa.dpos.y= f;
			}else if(strcmp(var, "angle=")==0 && loadexact){
				sscanf(dataval, "%f", &f);
				xa.angle= f;
			}else if(strcmp(var, "health=")==0 && loadexact){
				sscanf(dataval, "%f", &f);
				xa.health= f;
			}else if(strcmp(var, "gene_red=")==0){
				sscanf(dataval, "%f", &f);
				xa.gene_red= f;
			}else if(strcmp(var, "gene_gre=")==0){
				sscanf(dataval, "%f", &f);
				xa.gene_gre= f;
			}else if(strcmp(var, "gene_blu=")==0){
				sscanf(dataval, "%f", &f);
				xa.gene_blu= f;
			}else if(strcmp(var, "chamovid=")==0){
				sscanf(dataval, "%f", &f);
				xa.chamovid= f;
			}else if(strcmp(var, "sexprojectbias=")==0){
				sscanf(dataval, "%f", &f);
				xa.sexprojectbias= f;
			}else if(strcmp(var, "herb=")==0){
				sscanf(dataval, "%f", &f);
				xa.stomach[Stomach::PLANT]= f;
			}else if(strcmp(var, "carn=")==0){
				sscanf(dataval, "%f", &f);
				xa.stomach[Stomach::MEAT]= f;
			}else if(strcmp(var, "frug=")==0){
				sscanf(dataval, "%f", &f);
				xa.stomach[Stomach::FRUIT]= f;
			}else if(strcmp(var, "exhaustion=")==0 && loadexact){
				sscanf(dataval, "%f", &f);
				xa.exhaustion= f;
			}else if(strcmp(var, "carcasscount=")==0 && loadexact){
				sscanf(dataval, "%i", &i);
				xa.carcasscount= i;
			}else if(strcmp(var, "species=")==0){
				sscanf(dataval, "%i", &i);
				xa.species= i;
			}else if(strcmp(var, "kinrange=")==0){
				sscanf(dataval, "%i", &i);
				xa.kinrange= i;
			}else if(strcmp(var, "radius=")==0){
				sscanf(dataval, "%f", &f);
				xa.radius= f;
			}else if(strcmp(var, "spike=")==0 && loadexact){
				sscanf(dataval, "%f", &f);
				xa.spikeLength= f;
			}else if(strcmp(var, "jump=")==0 && loadexact){
				sscanf(dataval, "%f", &f);
				xa.jump= f;
			}else if((strcmp(var, "dfood=")==0 || strcmp(var, "dhealth=")==0) && loadexact){
				sscanf(dataval, "%f", &f);
				xa.dhealth= f;
			}else if(strcmp(var, "age=")==0 && loadexact){
				sscanf(dataval, "%i", &i);
				xa.age= i;
			}else if(strcmp(var, "gen=")==0){
				sscanf(dataval, "%i", &i);
				xa.gencount= i;
			}else if(strcmp(var, "hybrid=")==0){
				sscanf(dataval, "%i", &i);
				if(i==1) xa.hybrid= true;
				else xa.hybrid= false;
			}else if(strcmp(var, "cl1=")==0){
				sscanf(dataval, "%f", &f);
				xa.clockf1= f;
			}else if(strcmp(var, "cl2=")==0){
				sscanf(dataval, "%f", &f);
				xa.clockf2= f;
			}else if(strcmp(var, "smellmod=")==0){
				sscanf(dataval, "%f", &f);
				xa.smell_mod= f;
			}else if(strcmp(var, "hearmod=")==0){
				sscanf(dataval, "%f", &f);
				xa.hear_mod= f;
			}else if(strcmp(var, "bloodmod=")==0){
				sscanf(dataval, "%f", &f);
				xa.blood_mod= f;
			}else if(strcmp(var, "eyemod_agent=")==0){
				sscanf(dataval, "%f", &f);
				xa.eye_see_agent_mod= f;
			}else if(strcmp(var, "eyemod_cell=")==0){
				sscanf(dataval, "%f", &f);
				xa.eye_see_cell_mod= f;
			}else if(strcmp(var, "numbabies=")==0){
				sscanf(dataval, "%i", &i);
				xa.numbabies= i;
			}else if(strcmp(var, "metab=")==0){
				sscanf(dataval, "%f", &f);
				xa.metabolism= f;
			}else if(strcmp(var, "repcounter=")==0){
				sscanf(dataval, "%f", &f);
				xa.repcounter= f;
			}else if(strcmp(var, "temppref=")==0){
				sscanf(dataval, "%f", &f);
				xa.temperature_preference= f;
			}else if(strcmp(var, "lungs=")==0){
				sscanf(dataval, "%f", &f);
				xa.lungs= f;
			}else if(strcmp(var, "brain_mutchance=")==0){
				sscanf(dataval, "%f", &f);
				xa.brain_mutation_chance= f;
			}else if(strcmp(var, "brain_mutsize=")==0){
				sscanf(dataval, "%f", &f);
				xa.brain_mutation_size= f;
			}else if(strcmp(var, "gene_mutchance=")==0){
				sscanf(dataval, "%f", &f);
				xa.gene_mutation_chance= f;
			}else if(strcmp(var, "gene_mutsize=")==0){
				sscanf(dataval, "%f", &f);
				xa.gene_mutation_size= f;
			}else if(strcmp(var, "parentid=")==0){
				sscanf(dataval, "%i", &i);
				xa.parentid= i;
			}else if(strcmp(var, "freshkill=")==0 && loadexact){
				sscanf(dataval, "%i", &i);
				xa.freshkill= i;
			}else if(strcmp(var, "strength=")==0){
				sscanf(dataval, "%f", &f);
				xa.strength= f;
//			}else if(strcmp(var, "boxes=")==0){
//				sscanf(dataval, "%i", &i);
//				xa.brain.boxes.resize(i);
			}else if(strcmp(var, "conns=")==0){
				sscanf(dataval, "%i", &i);
				xa.brain.conns.resize(i);
			}else if(strcmp(var, "<y>")==0){
				mode= ReadWriteMode::EYE; //eye mode
			}else if(strcmp(var, "<n>")==0){
				mode= ReadWriteMode::CONN; //brain connection mode
			}else if(strcmp(var, "<x>")==0){
				mode= ReadWriteMode::BOX; //brain box mode
			}else if(strcmp(var, "<e>")==0){
				mode= ReadWriteMode::EAR; //ear mode
			}
		}else if(mode==ReadWriteMode::EYE){
			if(strcmp(var, "</y>")==0){
				mode= ReadWriteMode::AGENT; //revert to agent mode
			}else if(strcmp(var, "eye#=")==0){
				sscanf(dataval, "%i", &i);
				eyenum= i;
			}else if(strcmp(var, "eyedir=")==0){
				sscanf(dataval, "%f", &f);
				xa.eyedir[eyenum]= f;
			}else if(strcmp(var, "eyefov=")==0){
				sscanf(dataval, "%f", &f);
				xa.eyefov[eyenum]= f;
			}
		}else if(mode==ReadWriteMode::EAR){
			if(strcmp(var, "</e>")==0){
				mode= ReadWriteMode::AGENT; //revert to agent mode
			}else if(strcmp(var, "ear#=")==0){
				sscanf(dataval, "%i", &i);
				earnum= i;
			}else if(strcmp(var, "eardir=")==0){
				sscanf(dataval, "%f", &f);
				xa.eardir[earnum]= f;
			}else if(strcmp(var, "hearlow=")==0){
				sscanf(dataval, "%f", &f);
				xa.hearlow[earnum]= f;
			}else if(strcmp(var, "hearhigh=")==0){
				sscanf(dataval, "%f", &f);
				xa.hearhigh[earnum]= f;
			}
		}else if(mode==ReadWriteMode::BOX){
			if(strcmp(var, "</x>")==0){
				mode= ReadWriteMode::AGENT; //revert to agent mode
			}else if(strcmp(var, "box#=")==0){
				sscanf(dataval, "%i", &i);
				boxnum= i;
			}else if(strcmp(var, "kp=")==0){
				sscanf(dataval, "%f", &f);
				xa.brain.boxes[boxnum].kp= f;
			}else if(strcmp(var, "globalw=")==0){
				sscanf(dataval, "%f", &f);
				xa.brain.boxes[boxnum].gw= f;
			}else if(strcmp(var, "bias=")==0){
				sscanf(dataval, "%f", &f);
				xa.brain.boxes[boxnum].bias= f;
			}else if(strcmp(var, "seed=")==0){
				sscanf(dataval, "%i", &i);
				xa.brain.boxes[boxnum].seed= i;
			}else if(strcmp(var, "dead=")==0){
				sscanf(dataval, "%i", &i);
				if(i>=1) xa.brain.boxes[boxnum].dead= true;
				else xa.brain.boxes[boxnum].dead= false;
			}else if(strcmp(var, "target=")==0){
				sscanf(dataval, "%f", &f);
				xa.brain.boxes[boxnum].target= f;
			}else if(strcmp(var, "out=")==0){
				sscanf(dataval, "%f", &f);
				xa.brain.boxes[boxnum].out= f;
			}else if(strcmp(var, "oldout=")==0){
				sscanf(dataval, "%f", &f);
				xa.brain.boxes[boxnum].oldout= f;
			}
		}else if(mode==ReadWriteMode::CONN){
			if(strcmp(var, "</n>")==0){
				mode= ReadWriteMode::AGENT; //revert to agent mode
			}else if(strcmp(var, "conn#=")==0){
				sscanf(dataval, "%i", &i);
				connnum= i;
			}else if(strcmp(var, "type=")==0){
				sscanf(dataval, "%i", &i);
				xa.brain.conns[connnum].type = i;
			}else if(strcmp(var, "w=")==0){
				sscanf(dataval, "%f", &f);
				xa.brain.conns[connnum].w = f;
			}else if(strcmp(var, "sid=")==0){
				sscanf(dataval, "%i", &i);
				xa.brain.conns[connnum].sid = i;
			}else if(strcmp(var, "tid=")==0){
				sscanf(dataval, "%i", &i);
				xa.brain.conns[connnum].tid = i;
			}else if(strcmp(var, "seed=")==0){
				sscanf(dataval, "%i", &i);
				xa.brain.conns[connnum].seed = i;
			}
		}
	}
	printf("loaded agents.\n"); //report status
}


void ReadWrite::loadAgentFile(World *world, const char *address)
{
	//Some Notes: When this method is called, it's assumed that address is not blank or null
//	strcat(address,R::AGENT_SAVE_EXT);

	FILE* fl = fopen(address, "r");
	if(fl){
		loadAgents(world, fl, conf::VERSION, false);
		//note, for now, version numbers are not saved in agent files, so we force the default version number just to avoid trouble.
	}
	fclose(fl);
}


void ReadWrite::saveWorld(World *world, float xpos, float ypos, float scalemult, const char *filename)
{
	//Some Notes: When this method is called, it's assumed that filename is not blank or null
	std::string addressSAV;
	std::string addressREP;
	printf("Filename '%s' given. Saving...\n", filename);

	//set up our save file and report file addresses
	addressSAV= "saves\\";
	addressSAV.append(filename);
	addressREP= addressSAV;
	addressREP.append("_report.txt");

	addressSAV.append(R::WORLD_SAVE_EXT);

	//open save file, write over any previous, checking for the presence of the file has been relocated to GLView.cpp to allow GUI interactions
	FILE* fs = fopen(addressSAV.c_str(), "w");
	
	//start with saving world settings to compare with current
	fprintf(fs,"<world>\n");
	fprintf(fs,"V= %.2f\n",conf::VERSION);
	fprintf(fs,"BRAINBOXES= %i\n", world->BRAINBOXES);
	fprintf(fs,"INPUTS= %i\n", Input::INPUT_SIZE);
	fprintf(fs,"OUTPUTS= %i\n", Output::OUTPUT_SIZE);
	fprintf(fs,"WIDTH= %i\n", conf::WIDTH);
	fprintf(fs,"HEIGHT= %i\n", conf::HEIGHT);
	fprintf(fs,"CELLSIZE= %i\n", conf::CZ); //these saved values up till now are mostly for version control for now
	fprintf(fs,"AGENTS_SEE_CELLS= %i\n", world->AGENTS_SEE_CELLS);
	fprintf(fs,"AGENTS_DONT_OVERDONATE= %i\n", world->AGENTS_DONT_OVERDONATE);
	//save settings which have GUI controls
	fprintf(fs,"MOONLIT= %i\n", world->MOONLIT);
	fprintf(fs,"MOONLIGHTMULT= %f\n", world->MOONLIGHTMULT);
	fprintf(fs,"DROUGHTS= %i\n", world->DROUGHTS);
	fprintf(fs,"DROUGHTMULT= %f\n", world->DROUGHTMULT);
	fprintf(fs,"MUTEVENTS= %i\n", world->MUTEVENTS);
	fprintf(fs,"MUTEVENTMULT= %i\n", world->MUTEVENTMULT);
	fprintf(fs,"CLIMATE= %i\n", world->CLIMATE);
	fprintf(fs,"CLIMATEBIAS= %f\n", world->CLIMATEBIAS);
	fprintf(fs,"CLIMATEMULT= %f\n", world->CLIMATEMULT);
	fprintf(fs,"CLOSED= %i\n", world->isClosed());
	//if creating more GUI settings to save, please be sure to add them to two sections in GLView. Search ".cfg/.sav"
	fprintf(fs,"epoch= %i\n", world->current_epoch);
	fprintf(fs,"mod= %i\n", world->modcounter);
	fprintf(fs,"xpos= %f\n", xpos);
	fprintf(fs,"ypos= %f\n", ypos);
	fprintf(fs,"scale= %f\n", scalemult); //GLView xtranslate and ytranslate and scalemult
	for(int cx=0;cx<world->CW;cx++){ //start with the layers
		for(int cy=0;cy<world->CH;cy++){
			float food= world->cells[Layer::PLANTS][cx][cy];
			float meat= world->cells[Layer::MEATS][cx][cy];
			float hazard= world->cells[Layer::HAZARDS][cx][cy];
			float fruit= world->cells[Layer::FRUITS][cx][cy];
			float land= world->cells[Layer::ELEVATION][cx][cy];
			if(food+meat+hazard+fruit+land<=0) continue;
			fprintf(fs, "<c>\n"); //signals the writting of a cell
			fprintf(fs, "cx= %i\n", cx);
			fprintf(fs, "cy= %i\n", cy);
			if (food>0) fprintf(fs, "food= %f\n", food); //to further save space, we needn't report a value of a layer for the cell if it's zero
			if (meat>0) fprintf(fs, "meat= %f\n", meat);
			if (hazard>0) fprintf(fs, "hazard= %f\n", hazard);
			if (fruit>0) fprintf(fs, "fruit= %f\n", fruit);
			if (land>0) fprintf(fs, "land= %f\n", land);
			fprintf(fs,"</c>\n");
		}
	}

	for(int i=0; i<(int)world->agents.size(); i++){
		// here we save all agents. All simulation-significant data must be stored, from the pos and angle, to the change in food the bot was experiencing
		Agent* a= &world->agents[i];

		saveAgent(a, fs);
	}
	fprintf(fs,"</world>");
	fclose(fs);


	//now copy over report.txt logs if demo mode was disabled
	if(!world->isDemo()){
		char line[1028], *pos;

		//first, check if the last epoch and day in the saved report matches or is one less than the first one in the current report
		FILE* fr = fopen("report.txt", "r"); 
		FILE* ft = fopen(addressREP.c_str(), "r"); 
		bool append= false;
		char epochtext[8], daytext[8]; //for checking
		int epoch;
		int maxepoch= -1;
		int day;
		int maxday= -1;

		if(ft){
			printf("Old report.txt found, ");
			while(!feof(ft)){
				fgets(line, sizeof(line), ft);
				pos= strtok(line,"\n");
				sscanf(line, "%s%i%s%i%*s", &epochtext, &epoch, &daytext, &day);
				if (strcmp(epochtext, "Epoch:")==0) {
					if (epoch>=maxepoch) {
						maxepoch= epoch;
						maxday = day;
					}
				}
			}
			fclose(ft);

			if(world->isDebug()) printf("its last epoch was %i and day was %i.\n", maxepoch, maxday);
			
			//now compare the max epoch from original with the first entry of the new
			if(fr){
				fgets(line, sizeof(line), fr);
				pos= strtok(line,"\n");
				sscanf(line, "%s%i%s%i%*s", &epochtext, &epoch, &daytext, &day);
				if (strcmp(epochtext, "Epoch:")==0) {
					//if it is, we append, because this is (very likely) a continuation of that save
					if(world->isDebug()) printf("Our report.txt starts at epoch %i and day %i, ", epoch, day);
					if ((epoch==maxepoch || epoch==maxepoch+1) && (day==maxday || day==maxday+1 || (maxday==1 && day>1))){
						append= true;
						printf("epoch and day numbers match. Apending to it.\n");
					} else printf("Replacing it.\n");
				}
				rewind(fr);
			}
			//otherwise, we overwrite!
		} else {
			printf("No old report.txt found. Continuing normally.\n");
		}
		
		ft = append ? fopen(addressREP.c_str(), "a") : fopen(addressREP.c_str(), "w");
		if(fr){
			if(world->isDebug()) printf("Copying report.txt to save file\n");
			while(!feof(fr)){
				fgets(line, sizeof(line), fr);
				fprintf(ft, line);
			}
		} else {
			printf("report.txt didn\'t exist. That\'s... odd... Stanley, what did you do?!\n");
		}
		fclose(fr); fclose(ft);

		if(append) {
			//if we appended, then clear the current report so that we can save to the saved file's report once again if we don't restart the program
			fopen("report.txt", "w");
		}

	} else printf("Demo mode was active; no report data was ready.\n");
	
	printf("World Saved!\n");
}

void ReadWrite::loadWorld(World *world, float &xtranslate, float &ytranslate, float &scalemult, const char *filename)
{
	//Some Notes: When this method is called, it's assumed that filename is not blank or null
	std::string address;
	char line[64], *pos;
	char var[32];
	char dataval[16];
	int cxl= 0;
	int cyl= 0;
	int mode= ReadWriteMode::READY;//loading mode: -1= off, 0= world, 1= cell, 2= agent, 3= box, 4= connection, 5= eyes, 6= ears

	bool t1= false; //triggers for keeping track of where exactly we are

	float fileversion= 0; //version 0.05+ upgrade tool
	int i; //integer buffer
	float f; //float buffer

	address= "saves\\";
	address.append(filename);
	address.append(R::WORLD_SAVE_EXT);

	FILE *fl;
	fl= fopen(address.c_str(), "r");
	if(fl){
		printf("file '%s' exists! loading.\n", address.c_str());
		//real quick: don't keep user control active from last world
		world->pcontrol= false;
		//also disable demo mode
		world->setDemo(false);

		while(!feof(fl)){
			fgets(line, sizeof(line), fl);
			pos= strtok(line,"\n");
			sscanf(line, "%s%s", var, dataval);

			if(mode==ReadWriteMode::READY){
				if(strcmp(var, "<world>")==0){ //strcmp= 0 when the arguements equal
					//if we find a <world> tag, enable world loading and reset. simple
					mode= ReadWriteMode::WORLD;
					world->reset();
					printf("discovered world.\n"); //report status
				} else if(strcmp(var, "<a>")==0){ //UNUSED
					//if we instead immediately find an <a> tag, switch to agent loading mode - this save was only made with agents and we're meant to only load them
					mode= ReadWriteMode::AGENT;
					world->sanitize();
					printf("discovered agent database.\n"); //report status
				}
			}else if(mode==ReadWriteMode::WORLD){
				if(strcmp(var, "</world>")==0){ //check for end of world flag, indicating we're done
					mode= ReadWriteMode::OFF;
				}else if(strcmp(var, "V=")==0){
					//version number
					sscanf(dataval, "%f", &f);
					if(f!=conf::VERSION) {
						printf("ALERT: Version Number different! Expected V= %.2f, found V= %.2f\n", conf::VERSION, f);
/*						if(f<0.04) {
							printf("ALERT: version number < 0.04 detected! Multiplying all cell values by 2!\n");
							cellmult= 2;
						} if (f<0.06) {
							printf("ALERT: version number < 0.06 detected! Agent temp preferences will be automatically inverted!\n");
						} if (f<0.07) {
							const char* climatestatus= world->CLIMATE ? "ENABLED" : "DISABLED";
							printf("ALERT: version number < 0.07 detected! World temperature variables are being corrected and Global Climate change is %s!\n", climatestatus);
							world->CLIMATEBIAS= 0.5;
							world->CLIMATEMULT= 1; //these settings ensure global climate matches what was used in versions less than 0.07
						}*/ //we are not converting old saves in version 0.07
					}
					fileversion= f;
				}else if(strcmp(var, "BRAINBOXES=")==0){
					sscanf(dataval, "%i", &i);
					world->BRAINBOXES= i;
				}else if(strcmp(var, "INPUTS=")==0){
					sscanf(dataval, "%i", &i);
					if(i!=Input::INPUT_SIZE) {
						printf("ALERT: Brain Input size different! Issues WILL occur! Press enter to try and continue. . .\n");
						cin.get();
					}
				}else if(strcmp(var, "OUTPUTS=")==0){
					sscanf(dataval, "%i", &i);
					if(i!=Output::OUTPUT_SIZE) {
						printf("ALERT: Brain Output size different! Issues WILL occur! Press enter to try and continue. . .\n");
						cin.get();
					}
				}else if(strcmp(var, "WIDTH=")==0){
					//this WILL be loaded soon
					sscanf(dataval, "%i", &i);
					if(i!=conf::WIDTH) {
						printf("ALERT: World Width different! Issues WILL occur! Press enter to try and continue. . .\n");
						cin.get();
					}
				}else if(strcmp(var, "HEIGHT=")==0){
					//this WILL be loaded soon
					sscanf(dataval, "%i", &i);
					if(i!=conf::HEIGHT) {
						printf("ALERT: World Height different! Issues WILL occur! Press enter to try and continue. . .\n");
						cin.get();
					}
				}else if(strcmp(var, "CELLSIZE=")==0){
					//this may be loaded soon
					sscanf(dataval, "%i", &i);
					if(i!=conf::CZ) {
						printf("ALERT: Cell Size different! Issues WILL occur! Press enter to try and continue. . .\n");
						cin.get();
					}
				}else if(strcmp(var, "AGENTS_SEE_CELLS=")==0){
					sscanf(dataval, "%i", &i);
					if(i==1) world->AGENTS_SEE_CELLS= true;
					else world->AGENTS_SEE_CELLS= false;
				}else if(strcmp(var, "AGENTS_DONT_OVERDONATE=")==0){
					sscanf(dataval, "%i", &i);
					if(i==1) world->AGENTS_DONT_OVERDONATE= true;
					else world->AGENTS_DONT_OVERDONATE= false;
				}else if(strcmp(var, "MOONLIT=")==0){
					sscanf(dataval, "%i", &i);
					if(i==1) world->MOONLIT= true;
					else world->MOONLIT= false;
				}else if(strcmp(var, "MOONLIGHTMULT=")==0){
					sscanf(dataval, "%f", &f);
					world->MOONLIGHTMULT= f;
				}else if(strcmp(var, "DROUGHTS=")==0){
					sscanf(dataval, "%i", &i);
					if(i>=1) world->DROUGHTS= true;
					else world->DROUGHTS= false;
				}else if(strcmp(var, "DROUGHTMULT=")==0){
					sscanf(dataval, "%f", &f);
					world->DROUGHTMULT= f;
				}else if(strcmp(var, "MUTEVENTS=")==0){
					sscanf(dataval, "%i", &i);
					if(i>=1) world->MUTEVENTS= true;
					else world->MUTEVENTS= false;
				}else if(strcmp(var, "MUTEVENTMULT=")==0){
					sscanf(dataval, "%i", &i);
					world->MUTEVENTMULT= i;
				}else if(strcmp(var, "CLIMATE=")==0){
					sscanf(dataval, "%i", &i);
					if(i>=1) world->CLIMATE= true;
					else world->CLIMATE= false;
				}else if(strcmp(var, "CLIMATEBIAS=")==0){
					sscanf(dataval, "%f", &f);
					world->CLIMATEBIAS= f;
				}else if(strcmp(var, "CLIMATEMULT=")==0){
					sscanf(dataval, "%f", &f);
					world->CLIMATEMULT= f;
//				}else if(strcmp(var, "connections=")==0){
					//conns count; NOT CURRENTLY USED
//				}else if(strcmp(var, "width=")==0){
					//world width; NOT CURRENTLY USED
//					sscanf(dataval, "%i", &i);
//					conf::WIDTH= i;
//				}else if(strcmp(var, "height=")==0){
					//world height; NOT CURRENTLY USED
//					sscanf(dataval, "%i", &i);
//					conf::HEIGHT= i;
//				}else if(strcmp(var, "cellsize=")==0){
					//CZ; NOT CURRENTLY USED
//					sscanf(dataval, "%i", &i);
//					conf::CZ= i;
				}else if(strcmp(var, "epoch=")==0){
					//epoch
					sscanf(dataval, "%i", &i);
					world->current_epoch= i;
				}else if(strcmp(var, "mod=")==0){
					//mod count
					sscanf(dataval, "%i", &i);
					world->modcounter= i;
				}else if(strcmp(var, "CLOSED=")==0){
					//closed state
					sscanf(dataval, "%i", &i);
					if (i==1) world->setClosed(true);
					else world->setClosed(false);
//				}else if(strcmp(var, "PAUSED=")==0){
//					//Paused state (always saves as false)
//					sscanf(dataval, "%i", &i);
//					if (i==1) ;
//					else ;
				}else if(strcmp(var, "xpos=")==0){
					//view screen location x
					sscanf(dataval, "%f", &f);
					xtranslate= f;
				}else if(strcmp(var, "ypos=")==0){
					//view screen location y
					sscanf(dataval, "%f", &f);
					ytranslate= f;
				}else if(strcmp(var, "scale=")==0){
					//view screen scalemult
					sscanf(dataval, "%f", &f);
					scalemult= f;
				}else if(strcmp(var, "<c>")==0){
					//cells tag activates cell reading mode
					mode= ReadWriteMode::CELL;
				}else if(strcmp(var, "<a>")==0){
					//agent tag activates agent reading mode
					//version 0.05: this is no longer a mode, but rather a whole another method. Should function identically
					loadAgents(world, fl, fileversion); //when we leave here, should be EOF					
				}
			}else if(mode==ReadWriteMode::CELL){
				if(strcmp(var, "</c>")==0){
					//"end cell" tag is checked for first, because of else condition
					mode= ReadWriteMode::WORLD;
					if (!t1) printf("loading cells.\n"); //report status
					t1= true;
				}else if(strcmp(var, "cx=")==0){
					sscanf(dataval, "%i", &i);
					cxl= i;
				}else if(strcmp(var, "cy=")==0){
					sscanf(dataval, "%i", &i);
					cyl= i;
				}else if(strcmp(var, "food=")==0){
					sscanf(dataval, "%f", &f);
					world->cells[Layer::PLANTS][cxl][cyl]= f;
				}else if(strcmp(var, "meat=")==0){
					sscanf(dataval, "%f", &f);
					world->cells[Layer::MEATS][cxl][cyl]= f;
				}else if(strcmp(var, "hazard=")==0){
					sscanf(dataval, "%f", &f);
					world->cells[Layer::HAZARDS][cxl][cyl]= f;
				}else if(strcmp(var, "fruit=")==0){
					sscanf(dataval, "%f", &f);
					world->cells[Layer::FRUITS][cxl][cyl]= f;
				}else if(strcmp(var, "land=")==0){
					sscanf(dataval, "%f", &f);
					world->cells[Layer::ELEVATION][cxl][cyl]= f;
				}		
			}
		}
		fclose(fl);

		printf("WORLD LOADED!\n");
		world->addEvent("World Loaded!", EventColor::MINT);

		world->setStatsAfterLoad();

		world->processCells(true);
		world->setInputs();
		world->brainsTick();
		world->processOutputs(true);
		world->processOutputs(true);
		world->processOutputs(true);
		world->processOutputs(true);
		world->processOutputs(true);

	} else { //DOH! the file doesn't exist!
		printf("ERROR: Save file specified, '%s' doesn't exist!\n", address.c_str());
	}
}
