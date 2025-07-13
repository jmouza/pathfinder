#pragma once

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

class INextButtonObserver
{
public:
    virtual ~INextButtonObserver() {};
    virtual void NotifyNextButton() = 0;
};

class IPreviousButtonObserver
{
public:
    virtual ~IPreviousButtonObserver() {};
    virtual void NotifyPreviousButton() = 0;
};

class IForwardButtonObserver
{
public:
    virtual ~IForwardButtonObserver() {};
    virtual void NotifyForwardButton() = 0;
};

class IBackwardButtonObserver
{
public:
    virtual ~IBackwardButtonObserver() {};
    virtual void NotifyBackwardButton() = 0;
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