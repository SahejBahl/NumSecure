#include <iostream>
#include <climits>

#ifndef MARMOSET_TESTING
int main();
#endif

unsigned int add_checksum( unsigned int n ){
 
    if(n>99999999){
        return UINT_MAX;
    }
    
    int total = 0;
    unsigned int temp = n;
    //loop through all of the digits
    for(int i=0;i<8;i++){
        int cur_num = temp % 10;
        
        //if even spot (8,6,4,2)
        if(i%2 == 0){
            //double then add up the digits
            cur_num *= 2;
            total += cur_num%10;
            cur_num /= 10;
            total += cur_num;
        }
        else{
            total += cur_num;
        }
        
        // remove the last digit
        temp /= 10;
    }
    
    //steps 3/4
    return n*10 + ((total*9) %10);
}

void apply_checksum_to_array( unsigned int array[], std::size_t capacity ){
    for(int i =0;i<capacity;i++){
        array[i] = add_checksum(array[i]);
    }
}

bool is_checksum_valid( unsigned int n ){
    unsigned int toCheck = n/10;
    if(add_checksum(toCheck) == n && n <= 999999999){
        return true;
    }
    return false;
}

unsigned int remove_checksum( unsigned int n ){
    if (is_checksum_valid(n) == false){
        return UINT_MAX;
            }        
    else {
            return n/10;
        }
}

void strip_checksum_from_array( unsigned int array[], std::size_t capacity ){
    for(int i =0;i<capacity;i++){
        if (is_checksum_valid(array[i]) == false){
            array[i] = UINT_MAX;
            }        
        else {
            array[i] = array[i]/10;
        }   
    }
}

#ifndef MARMOSET_TESTING
int main() {
	unsigned int value_to_protect{21352411};
	unsigned int protected_value = add_checksum(value_to_protect);
	std::cout << "The value " << value_to_protect
		<< " with the checksum added is " << protected_value
		<< "." << std::endl;
	
	if (is_checksum_valid(protected_value))
	{
		std::cout << "The checksum is valid." << std::endl;
	}
	else   {
		std::cout << "The checksum is invalid." << std::endl;
	} 
	const std::size_t QTY_VALUES {3};
	unsigned int value_series[QTY_VALUES] {20201122, 20209913, 20224012};
	
	apply_checksum_to_array(value_series, QTY_VALUES);
	
	std::cout << "Series with checksums added: ";
	for (std::size_t series_index {0};
		series_index < QTY_VALUES; series_index++)
	{
		std::cout << value_series[series_index] << " ";
	}

    std::cout << std::endl;
    return 0;
}
#endif
