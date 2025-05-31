/*
Abstract class representing a pathfinder algorithm. 
*/
class Algorithm 
{
public:
    virtual ~Algorithm() = default;
    virtual void Execute() const = 0;
};