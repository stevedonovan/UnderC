//-----------------------  common  ------------------------------------------
// *SJD* Have changed all 'int' to 'short'
typedef unsigned char   uchar;
typedef unsigned short  uint;
typedef unsigned long   ulong;

#define False           0
#define True            1

//#pragma pack(1)

struct ssamp_set {
    short   x, y, z;
};

struct RAUCAPHEAD {
    uchar       compress_file;
    uchar       version_file;
    uchar       version_sw;
    uchar       rau_id;
    char        rau_code[4];
    long        rau_coordinate[3];
        float           rau_orientation[9];
    short       sample_rate;
    long        burst_rate;
    uchar       sensor_type;
    float       gain[4];
    uchar       auto_gain_control;
    uchar       compress_mode;
    uchar       decimate_factor;
    short       velocity_max[3];
    short       acceleration_max[3];
    long        trigger_date;
    long     trigger_time;   // in seconds after midnight
    long        trigger_nano_sec;
    uchar       trigger_time_ok;
    short       trigger_sample;
    short       p_onset;
    short       s_onset;
    float       event_azmiths[3];
    uchar       channels;
    short       samples;
    short       data_len;
    uchar       expansion[30];
};


// NCU header
struct NCUCAPHEAD {
    uchar       compress_file;
    uchar       version_file;
    uchar       version_sw;
    long        trigger_date;
    long     trigger_time;
    uchar       no_rau_events;
    uchar       rau_id[20];
        char            rau_code[80];
    uchar       expansion[30];
};

typedef NCUCAPHEAD NCU;
typedef RAUCAPHEAD RAU;




