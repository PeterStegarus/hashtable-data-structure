# Put
For the put method, get the hashkey and enter the item in a list in hashtable with the InsLG function. The elements are entered lexicographically ordered. Implemented cases for inserting element into empty list, inserting to beginning of the list, insert inside the list, insert at the end of the list.

# Remove
For the remove method, check that the list is not empty. Then, list only has one item, reset list. If the list has more than one element, first element is removed, also move the head of the list.

# Get
The get method searches for the key in the corresponding hashkey list using the the cmpDNS compare function. It returns the element or NULL if not found.

# Find
The find method uses get: true if an element was returned, false
if NULL was returned.

# Print
Print all non-empty buckets.

# Print bucket
Print all elements from bucket.