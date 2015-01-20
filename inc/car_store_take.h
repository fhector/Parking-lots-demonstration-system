
typedef struct garage_information
    {
           int garage_num;
           int garage_null;
           int garage_take_car_num;
           int car_passward;       
    }Garage;
    
extern Garage garage[10];    
extern void garage_init(void);
extern int car_store(void);
extern int car_take(int st_car);