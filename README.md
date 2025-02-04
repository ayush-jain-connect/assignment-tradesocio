**Data Structure Used:**
  **Unordered Map:** Provides fast access to orders based on their symbols, enabling quick lookups.
  **Priority Queue:** Utilized to store buy limit orders, allowing for quick retrieval of the highest-priority order based on price. This 
                      ensures that orders are filled in the correct order when market ticks are processed.

**Performance:** The priority queue optimizes the execution of orders by ensuring that the most relevant orders are processed first, enhancing the system's responsiveness to market changes.
