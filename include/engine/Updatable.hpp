#pragma once

class Updatable
{
public:
    virtual ~Updatable() = default;
    virtual void update() = 0;
};