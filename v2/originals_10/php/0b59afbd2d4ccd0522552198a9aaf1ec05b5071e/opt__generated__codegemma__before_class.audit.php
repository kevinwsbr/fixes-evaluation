// Create an audit event for a new ticket creation
$auditEvent = new AuditEvent();
$auditEvent->event_id = Event::TICKET_CREATE;
$auditEvent->object_type = 'Ticket';
$auditEvent->object_id = $ticket->getId();
$auditEvent->staff_id = $staff->getId();
$auditEvent->save();
