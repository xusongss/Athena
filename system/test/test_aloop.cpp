//#include "ALooper.h"
#include <foundation/ALooper.h>
#include <foundation/AHandler.h>
#include <foundation/AString.h>
#include <foundation/AMessage.h>
#include <foundation/ADebug.h>
#include <iostream>
using namespace std;
using namespace Athena;

// static
static status_t PostAndAwaitResponse(
        const sp<AMessage> &msg, sp<AMessage> *response) {
			
    status_t err = msg->postAndAwaitResponse(response);

    if (err != OK) {
        return err;
    }

    if (!(*response)->findInt32("err", &err)) {
        err = OK;
    }

    return err;
}

class SimplePlayer:public AHandler
{
public:
	 SimplePlayer();
	status_t setDataSource(const char *path);
    status_t prepare();
    status_t start();
    status_t stop();
    status_t reset();
protected:
    virtual ~SimplePlayer();
    virtual void onMessageReceived(const sp<AMessage> &msg);
	status_t onPrepare();
    status_t onStart();
    status_t onStop();
    status_t onReset();
	enum {
		kWhatSetDataSource,
		kWhatSetSurface,
		kWhatPrepare,
		kWhatStart,
		kWhatStop,
		kWhatReset,
		kWhatDoMoreStuff,
	};
};
SimplePlayer::SimplePlayer(){
}
SimplePlayer::~SimplePlayer() {
}
status_t SimplePlayer::setDataSource(const char *path) {
    sp<AMessage> msg = new AMessage(kWhatSetDataSource, id());
    msg->setString("path", path);
    sp<AMessage> response;
    return PostAndAwaitResponse(msg, &response);
}
status_t SimplePlayer::prepare() {
    sp<AMessage> msg = new AMessage(kWhatPrepare, id());
    sp<AMessage> response;
    return PostAndAwaitResponse(msg, &response);
}

status_t SimplePlayer::start() {
    sp<AMessage> msg = new AMessage(kWhatStart, id());
    sp<AMessage> response;
    return PostAndAwaitResponse(msg, &response);
}

status_t SimplePlayer::stop() {
    sp<AMessage> msg = new AMessage(kWhatStop, id());
    sp<AMessage> response;
    return PostAndAwaitResponse(msg, &response);
}

status_t SimplePlayer::reset() {
    sp<AMessage> msg = new AMessage(kWhatReset, id());
    sp<AMessage> response;
    return PostAndAwaitResponse(msg, &response);
}

status_t SimplePlayer::onPrepare(){
	cout<<__FUNCTION__<<endl;
	status_t err = OK;
	return err;
}
status_t SimplePlayer::onStart(){
	cout<<__FUNCTION__<<endl;
	status_t err = OK;
	return err;
}
status_t SimplePlayer::onStop(){
	cout<<__FUNCTION__<<endl;
	status_t err = OK;
	return err;
}
status_t SimplePlayer::onReset(){
	cout<<__FUNCTION__<<endl;
	status_t err = OK;
	return err;
}
void SimplePlayer::onMessageReceived(const sp<AMessage> &msg) {
    status_t err;
	switch (msg->what()) {
        case kWhatSetDataSource:
		case kWhatPrepare:
            err = onPrepare();
            break;
		case kWhatStart:
            err = onStart();
            break;
		case kWhatStop:
            err = onStop();
            break;
		case kWhatReset:
            err = onReset();
            break;
	}

    uint32_t replyID;
    CHECK(msg->senderAwaitsResponse(&replyID));
    sp<AMessage> response = new AMessage;
    response->setInt32("err", err);
    response->postReply(replyID);
}
int main(int argc, const char * argv[])
{
	sp<SimplePlayer> player = new SimplePlayer;
	sp<ALooper> looper = new ALooper();
	looper->start();
	looper->registerHandler(player);
    while(1){
        player->prepare();
        player->start();
        player->stop();
        player->reset();
    }

	return 0;
}