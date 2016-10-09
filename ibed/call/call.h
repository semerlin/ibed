#ifndef CALL_H
#define CALL_H

typedef enum
{
    Idle,          /**< Before INVITE is sent or received  */
    Calling,       /**< After INVITE is sent		    */
    Incoming,      /**< After INVITE is received.	    */
    Early,         /**< After response with To tag.	    */
    Connecting,    /**< After 2xx is sent/received.	    */
    Confirmed,     /**< After ACK is sent/received.	    */
    Disconnected   /**< Session is terminated.		    */
}CallState;

#endif // CALL_H
