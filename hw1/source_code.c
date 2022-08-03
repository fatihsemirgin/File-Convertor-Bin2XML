#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <libxml/xmlschemastypes.h>

int swap_Big_Endian(int number);
int Bin2XML(char* inputfile, char* outputfile);
struct record {
	char name[64]; //utf16
	char surname[32]; //utf8
	char gender;
	char email[32];
	char phone_number[16];
	char address[32];
	char level_of_education[8];
	unsigned int income_level; // given little-endian
	unsigned int expenditure; // given big-endian
	char currency_unit[16];
	char currentMood[32];
	float height;
	unsigned int weight;
};
int Bin2XML(char* inputfile, char* outputfile)
	{
	FILE *xml_file;
	xml_file=fopen(outputfile, "w");	// Open a xml file.
	fprintf(xml_file,"<records>\n");
	struct record r1;
	int count=0;
	FILE *fptr;
	fptr = fopen(inputfile, "rb");	// Open .dat file.

	if (fptr == NULL)
		printf("File could not be opened, exiting program.\n");

	else {
		while(!feof(fptr)) {
			fread(&r1, sizeof(r1), 1, fptr);
			if (r1.income_level==0 && count!=0 ) {
				break;
			}
			r1.expenditure = swap_Big_Endian(r1.expenditure);	// swap big endian
			if(count>0 ) {
				fprintf(xml_file,"\t<row id='%d'>\n",count);
				fprintf(xml_file,"\t\t<name> %s </name>\n",r1.name);
				fprintf(xml_file,"\t\t<surname> %s </surname>\n",r1.surname);
				fprintf(xml_file,"\t\t<gender> %c </gender>\n",r1.gender);
				fprintf(xml_file,"\t\t<email> %s </email>\n",r1.email);
				fprintf(xml_file,"\t\t<phone_number> %s </phone_number>\n",r1.phone_number);
				fprintf(xml_file,"\t\t<address> %s </address>\n",r1.address);
				fprintf(xml_file,"\t\t<level_of_education> %s </level_of_education>\n",r1.level_of_education);
				fprintf(xml_file,"\t\t<income_level> %u </income_level>\n",r1.income_level);
				fprintf(xml_file,"\t\t<expenditure> %u </expenditure>\n",r1.expenditure);
				fprintf(xml_file,"\t\t<currency_unit> %s </currency_unit>\n",r1.currency_unit);
				fprintf(xml_file,"\t\t<currentMood> %s </currentMood>\n",r1.currentMood);
				fprintf(xml_file,"\t\t<height> %.2f </height>\n",r1.height);
				fprintf(xml_file,"\t\t<weight> %u </weight>\n",r1.weight);
				fprintf(xml_file,"\t</row>\n");
				fprintf(xml_file,"\n");
			}
			count++;
			//printf("%s %s %c %s %s %s %s %u %u %s %s %f %u \n",r1.name,r1.surname,r1.gender,r1.email,r1.phone_number,r1.address,r1.level_of_education,
			//r1.income_level,r1.expenditure,r1.currency_unit,r1.currentMood,r1.height,r1.weight);
		}
	}
	fprintf(xml_file,"</records>");

		return 0;
	}

int swap_Big_Endian(int number) { // For Big Endian (unsigned int expenditure)
	int byte0,byte1,byte2,byte3;
	byte0=(number & 0x000000FF) >> 0;
	byte1=(number & 0x0000FF00) >> 8;
	byte2=(number & 0x00FF0000) >> 16;
	byte3=(number & 0xFF000000) >> 24;
	return ( (byte0 << 24) | (byte1 << 16) | (byte2 << 8) | (byte3 << 0));
}

int main (int argC, char** argV) {
	
	Bin2XML("records.dat","AbdullahDinc2019510031_FatihSemirgin2019510068.xml");
	
	
	
	// We closed this section because the library we could not import succesfully here, it works on linux command prompt (Validation Part)
	/*
	if (argC <= 2) {
		printf("Usage: %s <XML Document Name> <XSD Document Name>\n", argV[0]);
		return 0;
	}
	xmlDocPtr doc;
	xmlSchemaPtr schema = NULL;
	xmlSchemaParserCtxtPtr ctxt;
	char *test = argV[1];
	char *check = argV[2];
	int ret;
	xmlLineNumbersDefault(1);

	ctxt = xmlSchemaNewParserCtxt(check);

	xmlSchemaSetParserErrors(ctxt, (xmlSchemaValidityErrorFunc) fprintf, (xmlSchemaValidityWarningFunc) fprintf, stderr);
	schema = xmlSchemaParse(ctxt);
	xmlSchemaFreeParserCtxt(ctxt);


	doc = xmlReadFile(test, NULL, 0);

	if (doc == NULL){
		fprintf(stderr, "Could not parse %s\n", test);
	}
	else{
		xmlSchemaValidCtxtPtr ctxt;

		ctxt = xmlSchemaNewValidCtxt(schema);
		xmlSchemaSetValidErrors(ctxt, (xmlSchemaValidityErrorFunc) fprintf, (xmlSchemaValidityWarningFunc) fprintf, stderr);
		ret = xmlSchemaValidateDoc(ctxt, doc);

		if (ret == 0){
			printf("%s validates\n", test);
		}
		else if (ret > 0){
			printf("%s fails to validate\n", test);
		}
		else{
			printf("%s validation generated an internal error\n", test);
		}
		xmlSchemaFreeValidCtxt(ctxt);
		xmlFreeDoc(doc);
	}


	if(schema != NULL)
		xmlSchemaFree(schema);

	xmlSchemaCleanupTypes();
	xmlCleanupParser();
	xmlMemoryDump();
	*/
	return 0;
}


