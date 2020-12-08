use std::env; // to get arugments passed to the program
use std::thread;
use std::time::Duration;

/*
* Print the number of partitions and the size of each partition
* @param vs A vector of vectors
*/
fn print_partition_info(vs: &Vec<Vec<usize>>){
    println!("Number of partitions = {}", vs.len());
    for i in 0..vs.len(){
        println!("\tsize of partition {} = {}", i, vs[i].len());
    }
}

/*
* Create a vector with integers from 0 to num_elements -1
* @param num_elements How many integers to generate
* @return A vector with integers from 0 to (num_elements - 1)
*/
fn generate_data(num_elements: usize) -> Vec<usize>{
    let mut v : Vec<usize> = Vec::new();
    for i in 0..num_elements{
        v.push(i);
    }
    return v;
}

/*
* Partition the data in the vector v into 2 vectors
* @param v Vector of integers
* @return A vector that contains 2 vectors of integers

*/
fn partition_data_in_two(v: &Vec<usize>) -> Vec<Vec<usize>>{
    let partition_size = v.len() / 2;
    // Create a vector that will contain vectors of integers
    let mut xs: Vec<Vec<usize>> = Vec::new();

    // Create the first vector of integers
    let mut x1 : Vec<usize> = Vec::new();
    // Add the first half of the integers in the input vector to x1
    for i in 0..partition_size{
        x1.push(v[i]);
    }
    // Add x1 to the vector that will be returned by this function
    xs.push(x1);

    // Create the second vector of integers
    let mut x2 : Vec<usize> = Vec::new();
    // Add the second half of the integers in the input vector to x2
    for i in partition_size..v.len(){
        x2.push(v[i]);
    }
    // Add x2 to the vector that will be returned by this function
    xs.push(x2);
    // Return the result vector
    xs
}

/*
* Sum up the all the integers in the given vector
* @param v Vector of integers
* @return Sum of integers in v
* Note: this function has the same code as the reduce_data function.
*       But don't change the code of map_data or reduce_data.
*/
fn map_data(v: &Vec<usize>) -> usize{
    let mut sum = 0;
    for i in v{
        sum += i;
    }
    sum
}

/*
* Sum up the all the integers in the given vector
* @param v Vector of integers
* @return Sum of integers in v
*/
fn reduce_data(v: &Vec<usize>) -> usize{
    let mut sum = 0;
    for i in v{
        sum += i;
    }
    sum
}

/*
* A single threaded map-reduce program
*/
fn main() {

    // Use std::env to get arguments passed to the program
    let args: Vec<String> = env::args().collect();
    if args.len() != 3 {
        println!("ERROR: Usage {} num_partitions num_elements", args[0]);
        return;
    }
    let num_partitions : usize = args[1].parse().unwrap();
    let num_elements : usize = args[2].parse().unwrap();
    if num_partitions < 1{
      println!("ERROR: num_partitions must be at least 1");
        return;
    }
    if num_elements < num_partitions{
        println!("ERROR: num_elements cannot be smaller than num_partitions");
        return;
    }

    // Generate data.
    let v = generate_data(num_elements);

    // PARTITION STEP: partition the data into 2 partitions
    let xs = partition_data_in_two(&v);

    // Print info about the partitions
    print_partition_info(&xs);

    let mut intermediate_sums : Vec<usize> = Vec::new();

    // MAP STEP: Process each partition

    // CHANGE CODE START: Don't change any code above this line

    // Change the following code to create 2 threads that run concurrently and each of which uses map_data() function to process one of the two partitions
    
    /*******************/
    // intermediate_sums.push(map_data(&xs[0]));
    // intermediate_sums.push(map_data(&xs[1]));
    let c_xs0 = xs[0].clone();
    let c_xs1 = xs[1].clone();
    let t1 = thread::spawn(move ||(map_data(&c_xs0)));
    let t2 = thread::spawn(move ||(map_data(&c_xs1)));
    let _r1 = t1.join().unwrap();
    let _r2 = t2.join().unwrap();
    /*******************/

    // CHANGE CODE END: Don't change any code below this line until the next CHANGE CODE comment

    // Print the vector with the intermediate sums
    println!("Intermediate sums = {:?}", intermediate_sums);

    // REDUCE STEP: Process the intermediate result to produce the final result
    let sum = reduce_data(&intermediate_sums);
    println!("Sum = {}", sum);

    // CHANGE CODE: Add code that does the following:
    // 1. Calls partition_data to partition the data into equal partitions
    // 2. Calls print_partition_info to print info on the partitions that have been created
    // 3. Creates one thread per partition and uses each thread to concurrently process one partition
    // 4. Collects the intermediate sums from all the threads
    // 5. Prints information about the intermediate sums
    // 5. Calls reduce_data to process the intermediate sums
    // 6. Prints the final sum computed by reduce_data
    /*******************/

    
    let mut my_intermediate_sums : Vec<usize> = Vec::new();
    let my_pd = partition_data(num_partitions, &v);
    
    let pd_clone = my_pd.clone();
    // let mut in_sums : Vec<usize> = Vec::new();
    let mut threads = vec![];
    
    print_partition_info(&my_pd);
    
    /* create one thread per partition and use it concurrently */
    for element in pd_clone{
        // let tmp_t = thread::spawn(move || (map_data(&element)) );
        threads.push(thread::spawn(move || (map_data(&element)) ));
        // let _tmp_r1 = tmp_t.join().unwrap();
    }
    /* Collect intermdeiate sums from all the threads */
    for handle in threads{
        let tmp = handle.join().unwrap();
        my_intermediate_sums.push(tmp);
    }
    /* Prints information about the intermediate sums */
    println!("Intermediate sums = {:?}", my_intermediate_sums);
    /* Calls reduce_data to process the intermediate sums */
    let my_sum = reduce_data(&my_intermediate_sums);
    /* Prints final sum computed by reduce_data */
    println!("Sum = {}", my_sum);

    // for i in 0..my_pd.len(){
    //     // my_intermediate_sums.push(map_data(&my_pd[i]));
    //     // my_intermediate_sums.push(_r);
    // }

    // for handle in threads{
    //     let _r = handle.join().unwrap();
    //     my_intermediate_sums.push(_r);
    // }
    
    // println!("Intermediate sums = {:?}", my_intermediate_sums);
    // let my_sum = reduce_data(&my_intermediate_sums);
    // println!("Sum = {}", my_sum);
    /*******************/
}

/*
* CHANGE CODE: code this function
* Note: Don't change the signature of this function
*
* Partitions the data into a number of partitions such that
* - the returned partitions contain all elements that are in the input vector
* - if num_elements is a multiple of num_partitions, then all partitions must have equal number of elements
* - if num_elements is not a multiple of num_partitions, some partitions can have one more element than other partitions
*
* @param num_partitions The number of partitions to create
* @param v The data to be partitioned
* @return A vector that contains vectors of integers
* 
*/
fn partition_data(num_partitions: usize, v: &Vec<usize>) -> Vec<Vec<usize>>{
    // Remove the following line which has been added to remove a compiler error
    // let partition_size = v.len()/2;
    // println!("num_partitions {}", num_partitions);
    // println!("partition_size(num_elements) {}", v.len());
    // println!("num_elements % num_partitions {}", v.len()%num_partitions);
    
    let mut xs: Vec<Vec<usize>> = Vec::new();
    let mut v_cpy = v.clone();
    let part_size = v.len()/num_partitions;

    // if v.len()%num_partitions == 0{
    //     // println!("is multiple");
    //     for _i in 0..num_partitions{
    //         let mut tmp: Vec<usize> = Vec::new();
    //         for j in 0..part_size{
    //             tmp.push(v[j]);
    //         }
    //         xs.push(tmp);
    //     }
    // }
    // else{
    //     let extra = v.len()%num_partitions;
    //     /* For each partition, write/push the same amount */
    //     while v_cpy.len() != 0{
    //         for i in 0..num_partitions{
    //             let last = v_cpy.pop().unwrap();
                
    //         }
    //     }
        // for _i in 0..v.len(){
        // for _i in 0..v_cpy.len(){
        //     let mut tmp: Vec<usize> = Vec::new();
        // // for _i in 0..num_partitions{
        //     for j in 0..num_partitions{
        //     // for _j in 0..v.len(){
        //         if v_cpy.len() != 0{
        //             // let end = v_cpy.len()-1;
        //             // tmp.push(v_cpy[end]);
        //             // tmp.push(v_cpy.pop());
        //             let last = v_cpy.pop().unwrap();
        //             println!("pushin {}", j);
        //             tmp.push(last);
        //         }
        //     }
        //     xs.push(tmp);
        // }
        
    // }
    // else{
    //     // println!("is not multiple");
    //     let extra = v.len()%num_partitions;
    //     let mut counter = 0;
    //     for _i in 0..num_partitions{
    //         let mut called = 0;
    //         let mut tmp: Vec<usize> = Vec::new();
    //         for j in 0..v.len(){
    //             tmp.push(v[j]);
    //                 if counter < extra && called == 0{
    //                     // println!("extra loop");
    //                     called = 1; 
    //                     // tmp.push(v[j+counter+1]);
    //                     tmp.push(v[v.len()-counter]);
    //                     counter = counter + 1;
    //                 }
    //         }
    //         xs.push(tmp);
    //     }

    // }

    // partition_data_in_two(v)
    xs
}
