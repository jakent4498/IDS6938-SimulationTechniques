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

//   for (int cur_lambda = 3; cur_lambda < 34; cur_lambda++)
   for (int cur_lambda = 3; cur_lambda < 8; cur_lambda++)
   {
      
	   //TODO Create MM1_Queue objects to capture the airport senario.
	   // JAK created 5 queues on 3/19
	   //************************************************************
	   MM1_Queue quCheckin;
	   quCheckin.set_mu(53);
	   quCheckin.set_lambda(cur_lambda);
	   quCheckin.autogenerate_new_arrivals(true);
	   quCheckin.initialize();
	   quCheckin.set_seed(1, rd());
	   std::cout << "Set mu to 53 lamdba to " << cur_lambda << " Expected Response time = " << quCheckin.get_expected_response_time() << std::endl;


	   MM1_Queue quTSA1;
	   quTSA1.set_mu(20);
	   quTSA1.set_lambda(cur_lambda);
	   quTSA1.autogenerate_new_arrivals(false);
	   quTSA1.set_seed(rd(), rd());
	   quTSA1.initialize();


	   MM1_Queue quTSA2;
	   quTSA2.set_mu(20);
	   quTSA2.set_lambda(cur_lambda);
	   quTSA2.autogenerate_new_arrivals(false);
	   quTSA2.set_seed(rd(), rd());
	   quTSA2.initialize();

	   MM1_Queue quTSA3;
	   quTSA3.set_mu(20);
	   quTSA3.set_lambda(cur_lambda);
	   quTSA3.autogenerate_new_arrivals(false);
	   quTSA3.set_seed(rd(), rd());
	   quTSA3.initialize();

	   MM1_Queue quBoard;
	   quBoard.set_mu(80);
	   quBoard.set_lambda(cur_lambda);
	   quBoard.autogenerate_new_arrivals(false);
	   quBoard.set_seed(rd(), rd());
	   quBoard.initialize();


   for (int i=0;
		//TODO: add is_within_error_range check
	   !quCheckin.is_within_error_range(0.002) ||
	   !quTSA1.is_within_error_range(0.002) ||
	   !quTSA2.is_within_error_range(0.002) //||
	  // !quTSA3.is_within_error_range(0.002) ||
//	   !quBoard.is_within_error_range(0.002) 
//	i<20			// Allow queue to get past start up where it is outside error range
	;i++)
   {
	   Customer cust = quCheckin.process_next_event();    // =  TODO: process next event;
	   Customer cust2 = quTSA1.process_next_event();   // =  TODO: process next event;
	   Customer cust3 = quTSA2.process_next_event();   // =  TODO: process next event;
	   Customer cust4 = quTSA3.process_next_event();   // =  TODO: process next event;
	   Customer cust5 = quBoard.process_next_event();	// JAK added 3/19 for boarding customer
	   //TODO: one more process_next_event for the last object.
	   
	   // JAK 3/19 have customers but what do they don
	   // Try setting the id to next and then how to add them to quCheckIn?
	   //cust.set_id(next);
/*	   cout << "i= " << i << " Expected Response time = " << quCheckin.get_expected_response_time();
	   cout << " mean resonse time = " << quCheckin.get_mean_response_time();
	   cout << " current time = " << quCheckin.get_current_time();
	   cout << " queue size = " << quCheckin.get_current_queue_size() << "\t";
	   if (quCheckin.is_within_error_range(0.002))
		   cout << "within error range" << endl;
	   else cout << "NOT within error range" << endl;
//	   cout << " idle prob = " << quCheckin.get_idle_prob() << endl;
/*	   std::cout << "cur_lambda = " << cur_lambda << "   in loop length of Checkin = " << quCheckin.get_current_queue_size() << std::endl;
	   std::cout << "get_mean_response_time " << quCheckin.get_mean_response_time() << "get_expected_response_time = " << quCheckin.get_expected_response_time() << std::endl;
	   std::cout << "get_mean_number_customers " << quCheckin.get_mean_number_customers() << "get_expected_number_customers " << quCheckin.get_expected_number_customers() << std::endl;
		   for (int myi=1; myi < 10; myi++) {
			   std::cout << "   in loop length of Checkin = " << quCheckin.get_current_queue_size() << std::endl;
			   quCheckin.process_next_event();
//			   quCheckin.add_external_arrival();
		   }
*/	  // quCheckin.add_external_arrival();		// how do I show cust just arrived at queue?

       if (cust.get_type() == Customer::COMPLETED())
       {
          switch(next)
          {
            case 0:
				//TODO add_external_arrival() for your security gates;
				quTSA1.add_external_arrival();
				cust2.set_type(Customer::ARRIVAL());
//				std::cout << "In case 0 quCheckin = " << quCheckin.get_current_queue_size() << "quTSA1= " << quTSA1.get_current_queue_size() << std::endl;
				//cust2.set_arrival(1.0);
				//quTSA1.process_next_event()
                 break;
            case 1:
				//TODO add_external_arrival() for your security gates;
				quTSA2.add_external_arrival();
				cust3.set_type(Customer::ARRIVAL());
				//				std::cout << "In cust3" << std::endl;
				break;
            case 2:
                //TODO add_external_arrival() for your security gates;
				quTSA3.add_external_arrival();
//				cust4.set_arrival(quTSA3.get_current_time());
				cust4.set_type(Customer::ARRIVAL()); 
//				std::cout << "In cust4" << std::endl;
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
//		   cust5.set_arrival(quBoard.get_current_time());
		   cust5.set_type(Customer::ARRIVAL());
       }
   }



   //TODO Output statistics airport senario.
   quCheckin.plot_results_output();

   quTSA1.output(); std::cout << "*****" << endl;


   //**************************************************************************



   }

   return(0);
}

