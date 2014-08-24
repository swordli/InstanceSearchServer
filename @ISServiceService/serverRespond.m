function serverRespondReturn = serverRespond(obj,clientId,result)
%serverRespond(obj,clientId,result)
%
%     Input:
%       clientId = (string)
%       result{:} = (string)
%   
%     Output:
%       serverRespondReturn = (string)

% Build up the argument lists.
values = { ...
   clientId, ...
   result, ...
   };
names = { ...
   'clientId', ...
   'result', ...
   };
types = { ...
   '{http://www.w3.org/2001/XMLSchema}string', ...
   '{http://www.w3.org/2001/XMLSchema}string[]', ...
   };

% Create the message, make the call, and convert the response into a variable.
soapMessage = createSoapMessage( ...
    'http://services.instancesearch.uit.com', ...
    'serverRespond', ...
    values,names,types,'document');
response = callSoapService( ...
    obj.endpoint, ...
    '', ...
    soapMessage);
serverRespondReturn = parseSoapResponse(response);
