# Put
Compute hashkey and insert the item in a bucket in hashtable. The items are entered lexicographically ordered. Implemented cases for inserting items into empty list, to the beginning of the list, inside the list, at the end of the list.

# Remove
Checks that the list is not empty. If list only has one item, reset list. If the list has more than one item and first item is removed, also move the head of the list.

# Get
Search for the key in the corresponding bucket. Returns the element or NULL if not found.

# Find
Calls get: true if an element was returned, false if NULL was returned.

# Print
Print all non-empty buckets.

# Print bucket
Print all elements from bucket.
