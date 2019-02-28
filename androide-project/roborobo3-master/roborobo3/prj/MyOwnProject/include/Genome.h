#ifndef GENOME_H
#define GENOME_H
class Genome
{
    private:        
        int genSize;
        int isPosMin;
        int isPosMax;
        std::vector<float> gene;

    public :

        Genome(int genSize);
        void initGenome();
        std::vector<float> getGenome();
        void setNucleo(int i,float value);
        void setGenome(std::vector<float> g);
        void setGenSize(int size);
        int getGenSize();
        void setNucleotideGenome(int iNucleo, float value);
};
#endif