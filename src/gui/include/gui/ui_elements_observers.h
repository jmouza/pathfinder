#pragma once

#include <string>

class IStartButtonObserver
{
public:
    virtual ~IStartButtonObserver() {};
    virtual void NotifyStartButton() = 0;
};

class IPauseButtonObserver
{
public:
    virtual ~IPauseButtonObserver() {};
    virtual void NotifyPauseButton() = 0;
};

class IResumeButtonObserver
{
public:
    virtual ~IResumeButtonObserver() {};
    virtual void NotifyResumeButton() = 0;
};

class IResetButtonObserver
{
public:
    virtual ~IResetButtonObserver() {};
    virtual void NotifyResetButton() = 0;
};

class IClearButtonObserver
{
public:
    virtual ~IClearButtonObserver() {};
    virtual void NotifyClearButton() = 0;
};

class IFinerGridButtonObserver
{
public:
    virtual ~IFinerGridButtonObserver() {};
    virtual void NotifyFinerGridButton() = 0;
};

class ICoarserGridButtonObserver
{
public:
    virtual ~ICoarserGridButtonObserver() {};
    virtual void NotifyCoarserGridButton() = 0;
};

class IAlgorithmSelectorObserver
{
public:
    virtual ~IAlgorithmSelectorObserver() {};
    virtual void NotifyAlgorithmSelector(std::string selected_algorithm) = 0;
};