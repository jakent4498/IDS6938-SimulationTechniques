/*
  A simple program that simulates 5 MM1 queues at an airport. The first queue
  feeds 3 other queues that work in parallel. These feed a final queue.
  Simulation runs until error below threshold and, at the end,
  a performance evaluation report is shown, and logs are generated
  for plotting and analysis.
*/

using namespace std;

#include <random>
#include "customer.h"
#include "mm1_queue.h"


std::random_device rd;

void pause()
{
 std::string sInputString;
 // Wait for input from stdin (the keyboard)
 cout << "Continue (y)?";
 std::cin >> sInputString;
}



int main(int argc, char* argv[])
{
   int next = 0;
//   test_random_number_generator();

   for (int cur_lambda = 3; cur_lambda < 34; cur_lambda++)
   {
      
	   //TODO Create MM1_Queue objects to capture the airport senario.
	   // JAK created 5 queues on 3/19
	   //************************************************************
	   MM1_Queue quCheckin;
	   quCheckin.set_mu(53);
	   quCheckin.set_lambda(cur_lambda);
	   quCheckin.autogenerate_new_arrivals(true);
	   std::cout << "Set mu to 53" << std::endl;


	   MM1_Queue quTSA1;
	   quTSA1.set_mu(20);
	   quTSA1.set_lambda(cur_lambda);
	   quTSA1.autogenerate_new_arrivals(false);
	   quTSA1.initialize();

	   MM1_Queue quTSA2;
	   quTSA2.set_mu(20);

	   MM1_Queue quTSA3;
	   quTSA3.set_mu(20);

	   MM1_Queue quBoard;
	   quBoard.set_mu(20);


   for (quCheckin.initialize();
		//TODO: add is_within_error_range check
	   quCheckin.is_within_error_range(0.002)
	   ;quCheckin.add_external_arrival())
   {
	   Customer cust  = quCheckin.process_next_event();    // =  TODO: process next event;
	   Customer cust2 = quTSA1.process_next_event();   // =  TODO: process next event;
	   Customer cust3 = quTSA2.process_next_event();   // =  TODO: process next event;
	   Customer cust4 = quTSA3.process_next_event();   // =  TODO: process next event;
	   Customer cust5 = quBoard.process_next_event();	// JAK added 3/19 for boarding customer
	   //TODO: one more process_next_event for the last object.
	   
	   // JAK 3/19 have customers but what do they do
	   // Try setting the id to next and then how to add them to quCheckIn?
	   //cust.set_id(next);
	   std::cout << "cur_lambda = " << cur_lambda << std::endl;
/*		   for (int myi=1; myi < 10; myi++) {
			   std::cout << "   in loop length of Checkin = " << quCheckin.get_current_queue_size() << std::endl;
			   cust = quCheckin.get_next_customer();
		   }
	  // quCheckin.add_external_arrival();		// how do I show cust just arrived at queue?
*/
       if (cust.get_type() == Customer::COMPLETED())
       {
          switch(next)
          {
            case 0:
				//TODO add_external_arrival() for your security gates;
				quTSA1.add_external_arrival();
				std::cout << "In case 0 quCheckin = " << quCheckin.get_current_queue_size() << "quTSA1= " << quTSA1.get_current_queue_size() << std::endl;
				//cust2.set_arrival(1.0);
				//quTSA1.process_next_event()
                 break;
            case 1:
				//TODO add_external_arrival() for your security gates;
				cust3 = cust;
				std::cout << "In cust3" << std::endl;
				break;
            case 2:
                //TODO add_external_arrival() for your security gates;
				cust4 = cust;
				std::cout << "In cust4" << std::endl;
				break;
          }
          next++;
          if (next%3==0) next = 0;
       }
       if (cust2.get_type() == Customer::COMPLETED() || cust3.get_type() == Customer::COMPLETED() || cust4.get_type() == Customer::COMPLETED())
       {
		   //TODO add_external_arrival(); on your final boarding MM1_Queue object
		   // JAK adding 3/19
		   quBoard.add_external_arrival();
		   cust5.set_arrival(1.0);
		   cust5.set_type(Customer::ARRIVAL());
       }
   }



   //TODO Output statistics airport senario.



   //**************************************************************************



   }

   return(0);
}

